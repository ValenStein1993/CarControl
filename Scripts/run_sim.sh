#!/usr/bin/env bash
# scripts/run_sim.sh
set -e
ROOT="$(cd "$(dirname "$0")/.." && pwd)"

cd "$ROOT/App"
colcon build
source "$ROOT/App/install/setup.bash"

cd "$ROOT/Testing/ros_simulation"
colcon build
source "$ROOT/Testing/ros_simulation/install/setup.bash"

python3 "$ROOT/Testing/ros_simulation/install/model/share/model/src/generate_model.py"
ros2 launch startup_sim launch_simulation.py