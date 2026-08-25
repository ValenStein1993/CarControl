#!/bin/bash

cd ~/MicroROS
source /opt/ros/jazzy/setup.bash
source install/local_setup.bash
ros2 run micro_ros_agent micro_ros_agent serial --dev /tmp/uart_mros -b 115200 -v6