#!/usr/bin/env bash
# Same as Scripts/run_sim.sh + Scripts/run_app.sh, without building (the image is already built)
# and with the simulation running headless.
set -e
ROOT=/carcontrol

source /opt/ros/jazzy/setup.bash
source "$ROOT/App/install/setup.bash"
source "$ROOT/Testing/ros_simulation/install/setup.bash"

# run_sim.sh
python3 "$ROOT/Testing/ros_simulation/install/model/share/model/src/generate_model.py"
ros2 launch startup_sim launch_simulation.py headless:=true &

# give Gazebo time to start and spawn the car
sleep 15

# run_app.sh
ros2 launch startup launch_nodes.py
