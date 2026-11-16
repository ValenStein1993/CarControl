// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from car_msgs:msg/DebugPlanner.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/debug_planner.h"


#ifndef CAR_MSGS__MSG__DETAIL__DEBUG_PLANNER__STRUCT_H_
#define CAR_MSGS__MSG__DETAIL__DEBUG_PLANNER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

/// Struct defined in msg/DebugPlanner in the package car_msgs.
typedef struct car_msgs__msg__DebugPlanner
{
  std_msgs__msg__Header header;
  int32_t length_path;
  int32_t idx_update_node;
} car_msgs__msg__DebugPlanner;

// Struct for a sequence of car_msgs__msg__DebugPlanner.
typedef struct car_msgs__msg__DebugPlanner__Sequence
{
  car_msgs__msg__DebugPlanner * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} car_msgs__msg__DebugPlanner__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CAR_MSGS__MSG__DETAIL__DEBUG_PLANNER__STRUCT_H_
