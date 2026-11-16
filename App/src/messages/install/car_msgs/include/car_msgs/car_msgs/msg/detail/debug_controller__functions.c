// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from car_msgs:msg/DebugController.idl
// generated code does not contain a copyright notice
#include "car_msgs/msg/detail/debug_controller__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
car_msgs__msg__DebugController__init(car_msgs__msg__DebugController * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    car_msgs__msg__DebugController__fini(msg);
    return false;
  }
  // yaw_rate
  // yaw
  // cn_yaw
  // speed
  // steering_angle
  // idx_closest_node
  // cte
  // heading_error
  return true;
}

void
car_msgs__msg__DebugController__fini(car_msgs__msg__DebugController * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // yaw_rate
  // yaw
  // cn_yaw
  // speed
  // steering_angle
  // idx_closest_node
  // cte
  // heading_error
}

bool
car_msgs__msg__DebugController__are_equal(const car_msgs__msg__DebugController * lhs, const car_msgs__msg__DebugController * rhs)
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
  // yaw_rate
  if (lhs->yaw_rate != rhs->yaw_rate) {
    return false;
  }
  // yaw
  if (lhs->yaw != rhs->yaw) {
    return false;
  }
  // cn_yaw
  if (lhs->cn_yaw != rhs->cn_yaw) {
    return false;
  }
  // speed
  if (lhs->speed != rhs->speed) {
    return false;
  }
  // steering_angle
  if (lhs->steering_angle != rhs->steering_angle) {
    return false;
  }
  // idx_closest_node
  if (lhs->idx_closest_node != rhs->idx_closest_node) {
    return false;
  }
  // cte
  if (lhs->cte != rhs->cte) {
    return false;
  }
  // heading_error
  if (lhs->heading_error != rhs->heading_error) {
    return false;
  }
  return true;
}

bool
car_msgs__msg__DebugController__copy(
  const car_msgs__msg__DebugController * input,
  car_msgs__msg__DebugController * output)
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
  // yaw_rate
  output->yaw_rate = input->yaw_rate;
  // yaw
  output->yaw = input->yaw;
  // cn_yaw
  output->cn_yaw = input->cn_yaw;
  // speed
  output->speed = input->speed;
  // steering_angle
  output->steering_angle = input->steering_angle;
  // idx_closest_node
  output->idx_closest_node = input->idx_closest_node;
  // cte
  output->cte = input->cte;
  // heading_error
  output->heading_error = input->heading_error;
  return true;
}

car_msgs__msg__DebugController *
car_msgs__msg__DebugController__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  car_msgs__msg__DebugController * msg = (car_msgs__msg__DebugController *)allocator.allocate(sizeof(car_msgs__msg__DebugController), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(car_msgs__msg__DebugController));
  bool success = car_msgs__msg__DebugController__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
car_msgs__msg__DebugController__destroy(car_msgs__msg__DebugController * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    car_msgs__msg__DebugController__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
car_msgs__msg__DebugController__Sequence__init(car_msgs__msg__DebugController__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  car_msgs__msg__DebugController * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(car_msgs__msg__DebugController)) {
      return false;
    }
    data = (car_msgs__msg__DebugController *)allocator.zero_allocate(size, sizeof(car_msgs__msg__DebugController), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = car_msgs__msg__DebugController__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        car_msgs__msg__DebugController__fini(&data[i - 1]);
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
car_msgs__msg__DebugController__Sequence__fini(car_msgs__msg__DebugController__Sequence * array)
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
      car_msgs__msg__DebugController__fini(&array->data[i]);
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

car_msgs__msg__DebugController__Sequence *
car_msgs__msg__DebugController__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  car_msgs__msg__DebugController__Sequence * array = (car_msgs__msg__DebugController__Sequence *)allocator.allocate(sizeof(car_msgs__msg__DebugController__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = car_msgs__msg__DebugController__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
car_msgs__msg__DebugController__Sequence__destroy(car_msgs__msg__DebugController__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    car_msgs__msg__DebugController__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
car_msgs__msg__DebugController__Sequence__are_equal(const car_msgs__msg__DebugController__Sequence * lhs, const car_msgs__msg__DebugController__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!car_msgs__msg__DebugController__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
car_msgs__msg__DebugController__Sequence__copy(
  const car_msgs__msg__DebugController__Sequence * input,
  car_msgs__msg__DebugController__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(car_msgs__msg__DebugController)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(car_msgs__msg__DebugController);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    car_msgs__msg__DebugController * data =
      (car_msgs__msg__DebugController *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!car_msgs__msg__DebugController__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          car_msgs__msg__DebugController__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!car_msgs__msg__DebugController__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
