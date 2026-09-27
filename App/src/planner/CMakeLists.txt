cmake_minimum_required(VERSION 3.8)
project(planner)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
find_package(rclcpp REQUIRED)
find_package(car_msgs REQUIRED)
find_package(common REQUIRED)
find_package(nav_msgs REQUIRED)



add_executable(planner src/planner.cpp)

target_include_directories(planner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

ament_target_dependencies(planner 
  rclcpp 
  car_msgs 
  common
  nav_msgs)
  
target_link_libraries(
  planner
)

install(TARGETS
  planner
  DESTINATION lib/${PROJECT_NAME}
)


ament_package()
