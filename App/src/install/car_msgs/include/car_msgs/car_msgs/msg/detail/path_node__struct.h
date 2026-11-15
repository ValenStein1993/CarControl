// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from car_msgs:msg/PathNode.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/path_node.h"


#ifndef CAR_MSGS__MSG__DETAIL__PATH_NODE__STRUCT_H_
#define CAR_MSGS__MSG__DETAIL__PATH_NODE__STRUCT_H_

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

/// Struct defined in msg/PathNode in the package car_msgs.
typedef struct car_msgs__msg__PathNode
{
  std_msgs__msg__Header header;
  float x;
  float y;
  float th;
  int32_t idx;
} car_msgs__msg__PathNode;

// Struct for a sequence of car_msgs__msg__PathNode.
typedef struct car_msgs__msg__PathNode__Sequence
{
  car_msgs__msg__PathNode * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} car_msgs__msg__PathNode__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CAR_MSGS__MSG__DETAIL__PATH_NODE__STRUCT_H_
