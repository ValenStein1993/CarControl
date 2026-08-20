#!/bin/bash
cd ../App
source install/setup.bash
cd ../Testing/CarModel
python3 generate_model.py
cd ..
source CarModel/Plugins/install/setup.bash
ros2 launch launch_gz_ros.py
read -p "Press Enter to close..."