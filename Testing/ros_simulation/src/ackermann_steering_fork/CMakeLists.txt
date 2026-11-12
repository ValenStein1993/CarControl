cmake_minimum_required(VERSION 3.16)

project(ackermann_steering_fork)

find_package(ament_cmake REQUIRED)
find_package(gz-sim8 REQUIRED)
find_package(gz-plugin2 REQUIRED COMPONENTS register)
find_package(gz-transport13 REQUIRED)
find_package(gz-msgs10 REQUIRED)
find_package(gz-math7 REQUIRED)
find_package(gz-common5 REQUIRED COMPONENTS profiler)

# Fork of the gz-sim 8.15.0 AckermannSteering system (see header for changes)
add_library(
    carcontrol_ackermann_steering
    SHARED
    src/AckermannSteering.cc
)

target_include_directories(
    carcontrol_ackermann_steering
    PUBLIC
    include
)

target_link_libraries(
    carcontrol_ackermann_steering
    gz-sim8::gz-sim8
    gz-plugin2::register
    gz-transport13::gz-transport13
    gz-msgs10::gz-msgs10
    gz-math7::gz-math7
    gz-common5::profiler
)

install(
    TARGETS carcontrol_ackermann_steering
    DESTINATION lib
)

ament_environment_hooks(
  "${CMAKE_CURRENT_SOURCE_DIR}/hooks/gazebo_plugin_path.sh"
)

ament_package()
