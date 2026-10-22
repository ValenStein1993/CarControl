cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(costmap)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(common REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(costmap src/costmap.cpp)

target_include_directories(costmap PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

ament_target_dependencies(costmap 
  rclcpp 
  common
  nav_msgs
  OpenCV
)
  
target_link_libraries(
  costmap
)

install(TARGETS
  costmap
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
