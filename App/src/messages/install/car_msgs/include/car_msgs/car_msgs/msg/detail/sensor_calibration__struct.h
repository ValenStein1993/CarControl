// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from car_msgs:msg/SensorCalibration.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/sensor_calibration.h"


#ifndef CAR_MSGS__MSG__DETAIL__SENSOR_CALIBRATION__STRUCT_H_
#define CAR_MSGS__MSG__DETAIL__SENSOR_CALIBRATION__STRUCT_H_

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

/// Struct defined in msg/SensorCalibration in the package car_msgs.
typedef struct car_msgs__msg__SensorCalibration
{
  std_msgs__msg__Header header;
  bool is_calibrated;
  float mpu6050_mean_accel_x;
  float mpu6050_mean_accel_y;
  float mpu6050_mean_accel_z;
  float mpu6050_var_accel_x;
  float mpu6050_var_accel_y;
  float mpu6050_var_accel_z;
  float mpu6050_mean_gyro_x;
  float mpu6050_mean_gyro_y;
  float mpu6050_mean_gyro_z;
  float mpu6050_var_gyro_x;
  float mpu6050_var_gyro_y;
  float mpu6050_var_gyro_z;
  float cjmcu103_mean_angle;
  float cjmcu103_var_angle;
  float cjmcu103_mean_anglespeed;
  float cjmcu103_var_anglespeed;
  float wheelencoder_var_rotspeed;
} car_msgs__msg__SensorCalibration;

// Struct for a sequence of car_msgs__msg__SensorCalibration.
typedef struct car_msgs__msg__SensorCalibration__Sequence
{
  car_msgs__msg__SensorCalibration * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} car_msgs__msg__SensorCalibration__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CAR_MSGS__MSG__DETAIL__SENSOR_CALIBRATION__STRUCT_H_
