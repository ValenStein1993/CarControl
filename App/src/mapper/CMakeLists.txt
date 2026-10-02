cmake_minimum_required(VERSION 3.8)
project(mapper)
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
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(Boost REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)

add_executable(mapper src/mapper.cpp)

target_include_directories(mapper PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${Boost_INCLUDE_DIRS}
)

ament_target_dependencies(mapper 
  rclcpp 
  car_msgs 
  common 
  nav_msgs
  sensor_msgs
  tf2
  tf2_geometry_msgs
)

target_link_libraries(
  mapper
  Boost::headers
)
install(TARGETS
  mapper
  DESTINATION lib/${PROJECT_NAME}
)


ament_package()
