cmake_minimum_required(VERSION 3.8)
project(startup_sim)

find_package(ament_cmake REQUIRED)

install(
  DIRECTORY src
  DESTINATION share/${PROJECT_NAME}
)

ament_package()