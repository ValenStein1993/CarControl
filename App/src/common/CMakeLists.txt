cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)

project(common)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(ament_index_cpp REQUIRED)
find_package(rclcpp REQUIRED)
find_package(yaml-cpp REQUIRED)

add_library(common INTERFACE)

target_include_directories(common INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(common INTERFACE
  ament_index_cpp::ament_index_cpp
  yaml-cpp::yaml-cpp
  rclcpp::rclcpp
)

# Install C++ headers
install(
  DIRECTORY include/
  DESTINATION include
)

# Install shared configuration
install(
  DIRECTORY config/
  DESTINATION share/${PROJECT_NAME}/config
)

# Install interface library
install(
  TARGETS common
  EXPORT common_targets
)

ament_export_targets(common_targets)
ament_export_dependencies(ament_index_cpp)
ament_package()