// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from car_msgs:msg/NodeState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/node_state.h"


#ifndef CAR_MSGS__MSG__DETAIL__NODE_STATE__STRUCT_H_
#define CAR_MSGS__MSG__DETAIL__NODE_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/NodeState in the package car_msgs.
typedef struct car_msgs__msg__NodeState
{
  bool localizer_is_ready;
} car_msgs__msg__NodeState;

// Struct for a sequence of car_msgs__msg__NodeState.
typedef struct car_msgs__msg__NodeState__Sequence
{
  car_msgs__msg__NodeState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} car_msgs__msg__NodeState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CAR_MSGS__MSG__DETAIL__NODE_STATE__STRUCT_H_
