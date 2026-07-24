#!/usr/bin/env bash
# scripts/build_microros_lib.sh
set -e

UTILS_DIR=Libs/micro_ros_stm32cubemx_utils/microros_static_library
EXTRA_PKGS=$UTILS_DIR/library_generation/extra_packages

mkdir -p "$EXTRA_PKGS"
rm -rf "$EXTRA_PKGS/car_msgs"
cp -r ./Interfaces/CarMessage "$EXTRA_PKGS/car_msgs"

sudo docker pull microros/micro_ros_static_library_builder:jazzy
sudo docker run -it --rm -v "$(pwd)":/project \
  --env MICROROS_LIBRARY_FOLDER=$UTILS_DIR \
  microros/micro_ros_static_library_builder:jazzy
