#!/bin/bash
cd ../App
source install/setup.bash
cd ../Testing
source CarModel/Plugins/install/setup.bash
ros2 launch launch_gz_ros.py