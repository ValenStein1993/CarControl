// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from car_msgs:msg/SensorMeasurements.idl
// generated code does not contain a copyright notice
#include "car_msgs/msg/detail/sensor_measurements__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
car_msgs__msg__SensorMeasurements__init(car_msgs__msg__SensorMeasurements * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    car_msgs__msg__SensorMeasurements__fini(msg);
    return false;
  }
  // mpu6050_accel_x
  // mpu6050_accel_y
  // mpu6050_accel_z
  // mpu6050_gyro_x
  // mpu6050_gyro_y
  // mpu6050_gyro_z
  // ina219_current
  // ina219_power
  // cjmcu103_angle
  // cjmcu103_anglespeed
  // wheelencoder_rotspeed
  // wheelencoder_translspeed
  return true;
}

void
car_msgs__msg__SensorMeasurements__fini(car_msgs__msg__SensorMeasurements * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // mpu6050_accel_x
  // mpu6050_accel_y
  // mpu6050_accel_z
  // mpu6050_gyro_x
  // mpu6050_gyro_y
  // mpu6050_gyro_z
  // ina219_current
  // ina219_power
  // cjmcu103_angle
  // cjmcu103_anglespeed
  // wheelencoder_rotspeed
  // wheelencoder_translspeed
}

bool
car_msgs__msg__SensorMeasurements__are_equal(const car_msgs__msg__SensorMeasurements * lhs, const car_msgs__msg__SensorMeasurements * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // mpu6050_accel_x
  if (lhs->mpu6050_accel_x != rhs->mpu6050_accel_x) {
    return false;
  }
  // mpu6050_accel_y
  if (lhs->mpu6050_accel_y != rhs->mpu6050_accel_y) {
    return false;
  }
  // mpu6050_accel_z
  if (lhs->mpu6050_accel_z != rhs->mpu6050_accel_z) {
    return false;
  }
  // mpu6050_gyro_x
  if (lhs->mpu6050_gyro_x != rhs->mpu6050_gyro_x) {
    return false;
  }
  // mpu6050_gyro_y
  if (lhs->mpu6050_gyro_y != rhs->mpu6050_gyro_y) {
    return false;
  }
  // mpu6050_gyro_z
  if (lhs->mpu6050_gyro_z != rhs->mpu6050_gyro_z) {
    return false;
  }
  // ina219_current
  if (lhs->ina219_current != rhs->ina219_current) {
    return false;
  }
  // ina219_power
  if (lhs->ina219_power != rhs->ina219_power) {
    return false;
  }
  // cjmcu103_angle
  if (lhs->cjmcu103_angle != rhs->cjmcu103_angle) {
    return false;
  }
  // cjmcu103_anglespeed
  if (lhs->cjmcu103_anglespeed != rhs->cjmcu103_anglespeed) {
    return false;
  }
  // wheelencoder_rotspeed
  if (lhs->wheelencoder_rotspeed != rhs->wheelencoder_rotspeed) {
    return false;
  }
  // wheelencoder_translspeed
  if (lhs->wheelencoder_translspeed != rhs->wheelencoder_translspeed) {
    return false;
  }
  return true;
}

bool
car_msgs__msg__SensorMeasurements__copy(
  const car_msgs__msg__SensorMeasurements * input,
  car_msgs__msg__SensorMeasurements * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // mpu6050_accel_x
  output->mpu6050_accel_x = input->mpu6050_accel_x;
  // mpu6050_accel_y
  output->mpu6050_accel_y = input->mpu6050_accel_y;
  // mpu6050_accel_z
  output->mpu6050_accel_z = input->mpu6050_accel_z;
  // mpu6050_gyro_x
  output->mpu6050_gyro_x = input->mpu6050_gyro_x;
  // mpu6050_gyro_y
  output->mpu6050_gyro_y = input->mpu6050_gyro_y;
  // mpu6050_gyro_z
  output->mpu6050_gyro_z = input->mpu6050_gyro_z;
  // ina219_current
  output->ina219_current = input->ina219_current;
  // ina219_power
  output->ina219_power = input->ina219_power;
  // cjmcu103_angle
  output->cjmcu103_angle = input->cjmcu103_angle;
  // cjmcu103_anglespeed
  output->cjmcu103_anglespeed = input->cjmcu103_anglespeed;
  // wheelencoder_rotspeed
  output->wheelencoder_rotspeed = input->wheelencoder_rotspeed;
  // wheelencoder_translspeed
  output->wheelencoder_translspeed = input->wheelencoder_translspeed;
  return true;
}

car_msgs__msg__SensorMeasurements *
car_msgs__msg__SensorMeasurements__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  car_msgs__msg__SensorMeasurements * msg = (car_msgs__msg__SensorMeasurements *)allocator.allocate(sizeof(car_msgs__msg__SensorMeasurements), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(car_msgs__msg__SensorMeasurements));
  bool success = car_msgs__msg__SensorMeasurements__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
car_msgs__msg__SensorMeasurements__destroy(car_msgs__msg__SensorMeasurements * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    car_msgs__msg__SensorMeasurements__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
car_msgs__msg__SensorMeasurements__Sequence__init(car_msgs__msg__SensorMeasurements__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  car_msgs__msg__SensorMeasurements * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(car_msgs__msg__SensorMeasurements)) {
      return false;
    }
    data = (car_msgs__msg__SensorMeasurements *)allocator.zero_allocate(size, sizeof(car_msgs__msg__SensorMeasurements), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = car_msgs__msg__SensorMeasurements__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        car_msgs__msg__SensorMeasurements__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
car_msgs__msg__SensorMeasurements__Sequence__fini(car_msgs__msg__SensorMeasurements__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      car_msgs__msg__SensorMeasurements__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

car_msgs__msg__SensorMeasurements__Sequence *
car_msgs__msg__SensorMeasurements__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  car_msgs__msg__SensorMeasurements__Sequence * array = (car_msgs__msg__SensorMeasurements__Sequence *)allocator.allocate(sizeof(car_msgs__msg__SensorMeasurements__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = car_msgs__msg__SensorMeasurements__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
car_msgs__msg__SensorMeasurements__Sequence__destroy(car_msgs__msg__SensorMeasurements__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    car_msgs__msg__SensorMeasurements__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
car_msgs__msg__SensorMeasurements__Sequence__are_equal(const car_msgs__msg__SensorMeasurements__Sequence * lhs, const car_msgs__msg__SensorMeasurements__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!car_msgs__msg__SensorMeasurements__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
car_msgs__msg__SensorMeasurements__Sequence__copy(
  const car_msgs__msg__SensorMeasurements__Sequence * input,
  car_msgs__msg__SensorMeasurements__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(car_msgs__msg__SensorMeasurements)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(car_msgs__msg__SensorMeasurements);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    car_msgs__msg__SensorMeasurements * data =
      (car_msgs__msg__SensorMeasurements *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!car_msgs__msg__SensorMeasurements__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          car_msgs__msg__SensorMeasurements__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!car_msgs__msg__SensorMeasurements__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
