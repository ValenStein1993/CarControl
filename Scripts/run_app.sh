#!/usr/bin/env bash
# scripts/run_sim.sh
set -e
ROOT="$(cd "$(dirname "$0")/.." && pwd)"

cd "$ROOT/App"
colcon build
source "$ROOT/App/install/setup.bash"

ros2 launch startup launch_nodes.py