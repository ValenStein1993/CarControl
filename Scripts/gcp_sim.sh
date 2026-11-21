#!/usr/bin/env bash

set -euo pipefail

PROJECT=project-69960bd1-c997-4ca4-a0e
REGION=us-east1
ZONE=us-east1-b
VM=carcontrol-sim-auto
MACHINE=n4d-standard-4
DISK_GB=30
MAX_RUN=${MAX_RUN:-4h}
REGISTRY=$REGION-docker.pkg.dev
IMAGE=$REGISTRY/$PROJECT/carcontrol/carcontrol-sim

GCE=(--project="$PROJECT" --zone="$ZONE")

start() {
    local tag=${1:-latest}
    local existing
    existing=$(gcloud compute instances list --project="$PROJECT" \
        --filter="name=$VM AND zone:$ZONE" --format='value(name)')

    if [[ -n $existing ]]; then
        echo "VM $VM is already running, reconnecting (image tag argument is ignored)."
    else
        # the image must exist, otherwise we would pay for a VM that can't start anything
        if ! gcloud artifacts docker images describe "$IMAGE:$tag" --project="$PROJECT" >/dev/null 2>&1; then
            echo "Image tag '$tag' not found in $IMAGE" >&2
            exit 1
        fi

        startup=$(mktemp)
        trap 'rm -f "$startup"' EXIT
        cat > "$startup" <<EOF
#!/bin/bash
set -e
export HOME=/var/lib/carcontrol
mkdir -p "\$HOME"
docker-credential-gcr configure-docker --registries=$REGISTRY
docker rm -f sim 2>/dev/null || true
docker run -d --name sim --shm-size=1g -p 127.0.0.1:8765:8765 $IMAGE:$tag
EOF

        gcloud compute instances create "$VM" "${GCE[@]}" \
            --machine-type="$MACHINE" \
            --image-family=cos-stable --image-project=cos-cloud \
            --boot-disk-size="${DISK_GB}GB" --boot-disk-type=hyperdisk-balanced \
            --provisioning-model=SPOT \
            --instance-termination-action=DELETE \
            --max-run-duration="$MAX_RUN" \
            --metadata-from-file=startup-script="$startup"
        rm -f "$startup"
        trap - EXIT

        echo
        echo "Started $VM with image tag '$tag'. It deletes itself after $MAX_RUN."
    fi

    # the VM needs time to boot and pull the image before the tunnel is useful
    local timeout_s=600 start_s=$SECONDS
    echo "Waiting for the simulation container (image pull takes a few minutes)..."
    until [[ $(gcloud compute ssh "$VM" "${GCE[@]}" --quiet --ssh-flag="-oConnectTimeout=10" \
        --command="docker inspect -f '{{.State.Running}}' sim" 2>/dev/null) == true ]]; do
        if (( SECONDS - start_s > timeout_s )); then
            echo "Simulation did not start within ${timeout_s}s. The VM is still running and billed." >&2
            echo "Delete it with: $0 stop" >&2
            exit 1
        fi
        sleep 10
    done

    # one SSH connection carries both the Foxglove tunnel and the log stream
    trap 'echo; echo "Tunnel closed. The VM is still running and billed. Reconnect: $0 start   Delete: $0 stop"' EXIT
    echo "Simulation is running. In Foxglove connect to ws://localhost:8765. Logs follow (Ctrl+C closes logs and tunnel)."
    gcloud compute ssh "$VM" "${GCE[@]}" -- -t -o ExitOnForwardFailure=yes \
        -L 8765:127.0.0.1:8765 'docker logs -f --tail 100 sim'
}

stop() {
    if [[ -z $(gcloud compute instances list --project="$PROJECT" \
        --filter="name=$VM AND zone:$ZONE" --format='value(name)') ]]; then
        echo "VM $VM does not exist, nothing to delete."
        return
    fi
    gcloud compute instances delete "$VM" "${GCE[@]}" --quiet
    echo "Deleted $VM and its disk."
}

case "${1:-}" in
    start) start "${2:-latest}" ;;
    stop)  stop ;;
    *)     echo "Usage: $0 {start [image-tag]|stop}"; exit 1 ;;
esac
