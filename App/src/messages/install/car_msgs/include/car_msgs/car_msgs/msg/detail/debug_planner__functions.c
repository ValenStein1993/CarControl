// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from car_msgs:msg/DebugPlanner.idl
// generated code does not contain a copyright notice
#include "car_msgs/msg/detail/debug_planner__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
car_msgs__msg__DebugPlanner__init(car_msgs__msg__DebugPlanner * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    car_msgs__msg__DebugPlanner__fini(msg);
    return false;
  }
  // length_path
  // idx_update_node
  return true;
}

void
car_msgs__msg__DebugPlanner__fini(car_msgs__msg__DebugPlanner * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // length_path
  // idx_update_node
}

bool
car_msgs__msg__DebugPlanner__are_equal(const car_msgs__msg__DebugPlanner * lhs, const car_msgs__msg__DebugPlanner * rhs)
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
  // length_path
  if (lhs->length_path != rhs->length_path) {
    return false;
  }
  // idx_update_node
  if (lhs->idx_update_node != rhs->idx_update_node) {
    return false;
  }
  return true;
}

bool
car_msgs__msg__DebugPlanner__copy(
  const car_msgs__msg__DebugPlanner * input,
  car_msgs__msg__DebugPlanner * output)
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
  // length_path
  output->length_path = input->length_path;
  // idx_update_node
  output->idx_update_node = input->idx_update_node;
  return true;
}

car_msgs__msg__DebugPlanner *
car_msgs__msg__DebugPlanner__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  car_msgs__msg__DebugPlanner * msg = (car_msgs__msg__DebugPlanner *)allocator.allocate(sizeof(car_msgs__msg__DebugPlanner), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(car_msgs__msg__DebugPlanner));
  bool success = car_msgs__msg__DebugPlanner__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
car_msgs__msg__DebugPlanner__destroy(car_msgs__msg__DebugPlanner * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    car_msgs__msg__DebugPlanner__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
car_msgs__msg__DebugPlanner__Sequence__init(car_msgs__msg__DebugPlanner__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  car_msgs__msg__DebugPlanner * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(car_msgs__msg__DebugPlanner)) {
      return false;
    }
    data = (car_msgs__msg__DebugPlanner *)allocator.zero_allocate(size, sizeof(car_msgs__msg__DebugPlanner), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = car_msgs__msg__DebugPlanner__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        car_msgs__msg__DebugPlanner__fini(&data[i - 1]);
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
car_msgs__msg__DebugPlanner__Sequence__fini(car_msgs__msg__DebugPlanner__Sequence * array)
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
      car_msgs__msg__DebugPlanner__fini(&array->data[i]);
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

car_msgs__msg__DebugPlanner__Sequence *
car_msgs__msg__DebugPlanner__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  car_msgs__msg__DebugPlanner__Sequence * array = (car_msgs__msg__DebugPlanner__Sequence *)allocator.allocate(sizeof(car_msgs__msg__DebugPlanner__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = car_msgs__msg__DebugPlanner__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
car_msgs__msg__DebugPlanner__Sequence__destroy(car_msgs__msg__DebugPlanner__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    car_msgs__msg__DebugPlanner__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
car_msgs__msg__DebugPlanner__Sequence__are_equal(const car_msgs__msg__DebugPlanner__Sequence * lhs, const car_msgs__msg__DebugPlanner__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!car_msgs__msg__DebugPlanner__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
car_msgs__msg__DebugPlanner__Sequence__copy(
  const car_msgs__msg__DebugPlanner__Sequence * input,
  car_msgs__msg__DebugPlanner__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(car_msgs__msg__DebugPlanner)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(car_msgs__msg__DebugPlanner);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    car_msgs__msg__DebugPlanner * data =
      (car_msgs__msg__DebugPlanner *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!car_msgs__msg__DebugPlanner__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          car_msgs__msg__DebugPlanner__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!car_msgs__msg__DebugPlanner__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
