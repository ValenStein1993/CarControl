#!/bin/bash
cd ../App
source install/setup.bash
cd ../Testing
source CarModel/Plugins/install/setup.bash
rviz2 -d monitor.rviz &
ros2 launch launch_gz_ros.py
read -p "Press Enter to close..."