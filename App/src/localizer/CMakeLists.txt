cmake_minimum_required(VERSION 3.8)
project(localizer)

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

add_executable(localizer src/localizer.cpp)

target_include_directories(localizer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/TinyEKF/src)
target_include_directories(localizer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

ament_target_dependencies(localizer rclcpp car_msgs common)

install(TARGETS
  localizer
  DESTINATION lib/${PROJECT_NAME}
)


ament_package()
