cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(car_msgs)

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/SensorMeasurements.msg"
  "msg/SensorCalibration.msg"
  "msg/VehicleState.msg"
  "msg/MotionControl.msg"
  "msg/NodeState.msg"
  "msg/DebugPlanner.msg"
  DEPENDENCIES std_msgs
)

ament_package()