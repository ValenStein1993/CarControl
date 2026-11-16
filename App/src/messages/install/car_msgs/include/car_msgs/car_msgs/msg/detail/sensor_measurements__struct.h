// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from car_msgs:msg/SensorMeasurements.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/sensor_measurements.h"


#ifndef CAR_MSGS__MSG__DETAIL__SENSOR_MEASUREMENTS__STRUCT_H_
#define CAR_MSGS__MSG__DETAIL__SENSOR_MEASUREMENTS__STRUCT_H_

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

/// Struct defined in msg/SensorMeasurements in the package car_msgs.
typedef struct car_msgs__msg__SensorMeasurements
{
  std_msgs__msg__Header header;
  float mpu6050_accel_x;
  float mpu6050_accel_y;
  float mpu6050_accel_z;
  float mpu6050_gyro_x;
  float mpu6050_gyro_y;
  float mpu6050_gyro_z;
  float ina219_current;
  float ina219_power;
  float cjmcu103_angle;
  float cjmcu103_anglespeed;
  float wheelencoder_rotspeed;
  float wheelencoder_translspeed;
} car_msgs__msg__SensorMeasurements;

// Struct for a sequence of car_msgs__msg__SensorMeasurements.
typedef struct car_msgs__msg__SensorMeasurements__Sequence
{
  car_msgs__msg__SensorMeasurements * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} car_msgs__msg__SensorMeasurements__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CAR_MSGS__MSG__DETAIL__SENSOR_MEASUREMENTS__STRUCT_H_
