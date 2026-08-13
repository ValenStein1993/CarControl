cmake_minimum_required(VERSION 3.5)
project(car_msgs)

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/SensorMeasurements.msg"
  "msg/SensorCalibration.msg"
  "msg/VehicleState.msg"
  "msg/MotionControl.msg"
)

ament_package()