// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from car_msgs:msg/NodeState.idl
// generated code does not contain a copyright notice
#include "car_msgs/msg/detail/node_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
car_msgs__msg__NodeState__init(car_msgs__msg__NodeState * msg)
{
  if (!msg) {
    return false;
  }
  // localizer_is_ready
  return true;
}

void
car_msgs__msg__NodeState__fini(car_msgs__msg__NodeState * msg)
{
  if (!msg) {
    return;
  }
  // localizer_is_ready
}

bool
car_msgs__msg__NodeState__are_equal(const car_msgs__msg__NodeState * lhs, const car_msgs__msg__NodeState * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // localizer_is_ready
  if (lhs->localizer_is_ready != rhs->localizer_is_ready) {
    return false;
  }
  return true;
}

bool
car_msgs__msg__NodeState__copy(
  const car_msgs__msg__NodeState * input,
  car_msgs__msg__NodeState * output)
{
  if (!input || !output) {
    return false;
  }
  // localizer_is_ready
  output->localizer_is_ready = input->localizer_is_ready;
  return true;
}

car_msgs__msg__NodeState *
car_msgs__msg__NodeState__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  car_msgs__msg__NodeState * msg = (car_msgs__msg__NodeState *)allocator.allocate(sizeof(car_msgs__msg__NodeState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(car_msgs__msg__NodeState));
  bool success = car_msgs__msg__NodeState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
car_msgs__msg__NodeState__destroy(car_msgs__msg__NodeState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    car_msgs__msg__NodeState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
car_msgs__msg__NodeState__Sequence__init(car_msgs__msg__NodeState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  car_msgs__msg__NodeState * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(car_msgs__msg__NodeState)) {
      return false;
    }
    data = (car_msgs__msg__NodeState *)allocator.zero_allocate(size, sizeof(car_msgs__msg__NodeState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = car_msgs__msg__NodeState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        car_msgs__msg__NodeState__fini(&data[i - 1]);
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
car_msgs__msg__NodeState__Sequence__fini(car_msgs__msg__NodeState__Sequence * array)
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
      car_msgs__msg__NodeState__fini(&array->data[i]);
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

car_msgs__msg__NodeState__Sequence *
car_msgs__msg__NodeState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  car_msgs__msg__NodeState__Sequence * array = (car_msgs__msg__NodeState__Sequence *)allocator.allocate(sizeof(car_msgs__msg__NodeState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = car_msgs__msg__NodeState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
car_msgs__msg__NodeState__Sequence__destroy(car_msgs__msg__NodeState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    car_msgs__msg__NodeState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
car_msgs__msg__NodeState__Sequence__are_equal(const car_msgs__msg__NodeState__Sequence * lhs, const car_msgs__msg__NodeState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!car_msgs__msg__NodeState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
car_msgs__msg__NodeState__Sequence__copy(
  const car_msgs__msg__NodeState__Sequence * input,
  car_msgs__msg__NodeState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(car_msgs__msg__NodeState)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(car_msgs__msg__NodeState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    car_msgs__msg__NodeState * data =
      (car_msgs__msg__NodeState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!car_msgs__msg__NodeState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          car_msgs__msg__NodeState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!car_msgs__msg__NodeState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
