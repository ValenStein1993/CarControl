# syntax=docker/dockerfile:1
#
# Headless CarControl simulation: Gazebo Harmonic + App stack (Cartographer, planner, controller, odometry).
# Sensors are rendered in software (Mesa llvmpipe via EGL), no GPU or display needed.
#
# build (from the repository root):
#   docker build -f Docker/Dockerfile -t carcontrol-sim .
# run:
#   docker run --rm -it --shm-size=1g carcontrol-sim

FROM ros:jazzy-ros-base

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential \
        cmake \
        python3-colcon-common-extensions \
        ros-jazzy-ros-gz \
        ros-jazzy-cartographer-ros \
        ros-jazzy-tf2-ros \
        ros-jazzy-tf2-geometry-msgs \
        ros-jazzy-foxglove-bridge \
        ros-jazzy-rosbag2-storage-mcap \
        libopencv-dev \
        libeigen3-dev \
        python3-jinja2 \
        python3-yaml \
        python3-numpy \
        libegl1 \
        libegl-mesa0 \
        libgl1-mesa-dri \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /carcontrol

# ---- App workspace (car_msgs, common, odometry, planner, controller, costmap, startup) ----
# config.yaml is compiled into config.hpp here -> config changes need a rebuild of the image
COPY App/src App/src
RUN . /opt/ros/jazzy/setup.sh \
    && cd App \
    && colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release \
    && rm -rf build log

# ---- simulation workspace (Gazebo plugins, message bridge, model, sim launch) ----
COPY Testing/ros_simulation/src Testing/ros_simulation/src
RUN . /opt/ros/jazzy/setup.sh \
    && . App/install/setup.sh \
    && cd Testing/ros_simulation \
    && colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release \
    && rm -rf build log

COPY Docker/entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

# software OpenGL for the gpu_lidar; set to 0 on a GPU host (docker run --gpus all -e LIBGL_ALWAYS_SOFTWARE=0)
ENV LIBGL_ALWAYS_SOFTWARE=1

ENTRYPOINT ["/entrypoint.sh"]
