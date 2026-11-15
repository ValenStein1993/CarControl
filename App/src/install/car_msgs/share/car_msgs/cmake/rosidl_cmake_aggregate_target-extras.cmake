# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target car_msgs::car_msgs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${car_msgs_TARGETS}.
if(car_msgs_TARGETS AND NOT TARGET car_msgs::car_msgs)
  add_library(car_msgs::car_msgs INTERFACE IMPORTED)
  set_target_properties(car_msgs::car_msgs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${car_msgs_TARGETS}")
endif()
