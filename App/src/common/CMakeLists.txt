cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)

project(common)

find_package(Python3 REQUIRED COMPONENTS Interpreter)

set(YAML_FILE "${CMAKE_CURRENT_SOURCE_DIR}/config/config.yaml")
set(HEADER_FILE "${CMAKE_CURRENT_BINARY_DIR}/config/config.hpp")
set(SCRIPT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/config/gen_config_hpp.py")

# Tell CMake to run Python when config.yaml updates
add_custom_command(
    OUTPUT "${HEADER_FILE}"
    COMMAND ${Python3_EXECUTABLE} "${SCRIPT_FILE}" "${YAML_FILE}" "${HEADER_FILE}"
    DEPENDS "${YAML_FILE}" "${SCRIPT_FILE}"
    VERBATIM
    COMMENT "Generating C++ header from YAML"
)

add_custom_target(common_config_header ALL DEPENDS "${HEADER_FILE}")

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(ament_index_cpp REQUIRED)
find_package(rclcpp REQUIRED)

add_library(common INTERFACE)

target_include_directories(common INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(common INTERFACE
  ament_index_cpp::ament_index_cpp
  rclcpp::rclcpp
)

add_dependencies(common common_config_header)

# Install C++ headers
install(
  DIRECTORY include/
  DESTINATION include
)

install(
  FILES "${HEADER_FILE}"
  DESTINATION include/common
)

# Install shared configuration
install(
  DIRECTORY config/
  DESTINATION share/common/config
)

# Install interface library
install(
  TARGETS common
  EXPORT common_targets
)


ament_export_targets(common_targets)
ament_export_dependencies(ament_index_cpp)
ament_package()