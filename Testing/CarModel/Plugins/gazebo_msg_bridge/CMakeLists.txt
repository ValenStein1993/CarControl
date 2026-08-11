cmake_minimum_required(VERSION 3.16)

project(gazebo_msg_bridge)


find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(gz-sim8 REQUIRED)
find_package(car_msgs REQUIRED)
find_package(gz-transport13 REQUIRED)


add_library(
    gazebo_msg_bridge
    SHARED
    src/MessageBridge.cpp
)


target_include_directories(
    gazebo_msg_bridge
    PUBLIC
    include
)


ament_target_dependencies(
    gazebo_msg_bridge
    rclcpp
    sensor_msgs
    car_msgs
    gz-transport13
)

target_link_libraries(
    gazebo_msg_bridge
    gz-sim8::gz-sim8
    gz-transport13::gz-transport13
)


install(
    TARGETS gazebo_msg_bridge
    DESTINATION lib
)

ament_environment_hooks(
  "${CMAKE_CURRENT_SOURCE_DIR}/hooks/gazebo_plugin_path.sh"
)

ament_package()
