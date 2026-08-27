cmake_minimum_required(VERSION 3.8)
project(localizer)
set(CMAKE_CXX_STANDARD 20)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(rclcpp REQUIRED)
find_package(car_msgs REQUIRED)
find_package(common REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)

add_executable(localizer src/localizer.cpp)

target_include_directories(localizer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/TinyEKF/src)
target_include_directories(localizer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

ament_target_dependencies(localizer 
  rclcpp 
  car_msgs 
  common 
  geometry_msgs 
  tf2_ros 
  nav_msgs
  tf2
  tf2_geometry_msgs)

target_link_libraries(
  localizer
  yaml-cpp::yaml-cpp
)
install(TARGETS
  localizer
  DESTINATION lib/${PROJECT_NAME}
)


ament_package()
