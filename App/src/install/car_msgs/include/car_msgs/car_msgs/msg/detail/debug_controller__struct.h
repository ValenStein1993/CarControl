// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from car_msgs:msg/DebugController.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/debug_controller.h"


#ifndef CAR_MSGS__MSG__DETAIL__DEBUG_CONTROLLER__STRUCT_H_
#define CAR_MSGS__MSG__DETAIL__DEBUG_CONTROLLER__STRUCT_H_

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

/// Struct defined in msg/DebugController in the package car_msgs.
typedef struct car_msgs__msg__DebugController
{
  std_msgs__msg__Header header;
  float yaw_rate;
  float yaw;
  float cn_yaw;
  float speed;
  float steering_angle;
  int32_t pdx_cnode;
  float cte;
  float heading_error;
} car_msgs__msg__DebugController;

// Struct for a sequence of car_msgs__msg__DebugController.
typedef struct car_msgs__msg__DebugController__Sequence
{
  car_msgs__msg__DebugController * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} car_msgs__msg__DebugController__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CAR_MSGS__MSG__DETAIL__DEBUG_CONTROLLER__STRUCT_H_
