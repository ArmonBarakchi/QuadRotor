// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from quadrotor_msgs:msg/DroneControl.idl
// generated code does not contain a copyright notice
#include "quadrotor_msgs/msg/detail/drone_control__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
quadrotor_msgs__msg__DroneControl__init(quadrotor_msgs__msg__DroneControl * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    quadrotor_msgs__msg__DroneControl__fini(msg);
    return false;
  }
  // force_des
  // torque
  return true;
}

void
quadrotor_msgs__msg__DroneControl__fini(quadrotor_msgs__msg__DroneControl * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // force_des
  // torque
}

bool
quadrotor_msgs__msg__DroneControl__are_equal(const quadrotor_msgs__msg__DroneControl * lhs, const quadrotor_msgs__msg__DroneControl * rhs)
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
  // force_des
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->force_des[i] != rhs->force_des[i]) {
      return false;
    }
  }
  // torque
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->torque[i] != rhs->torque[i]) {
      return false;
    }
  }
  return true;
}

bool
quadrotor_msgs__msg__DroneControl__copy(
  const quadrotor_msgs__msg__DroneControl * input,
  quadrotor_msgs__msg__DroneControl * output)
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
  // force_des
  for (size_t i = 0; i < 3; ++i) {
    output->force_des[i] = input->force_des[i];
  }
  // torque
  for (size_t i = 0; i < 3; ++i) {
    output->torque[i] = input->torque[i];
  }
  return true;
}

quadrotor_msgs__msg__DroneControl *
quadrotor_msgs__msg__DroneControl__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  quadrotor_msgs__msg__DroneControl * msg = (quadrotor_msgs__msg__DroneControl *)allocator.allocate(sizeof(quadrotor_msgs__msg__DroneControl), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(quadrotor_msgs__msg__DroneControl));
  bool success = quadrotor_msgs__msg__DroneControl__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
quadrotor_msgs__msg__DroneControl__destroy(quadrotor_msgs__msg__DroneControl * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    quadrotor_msgs__msg__DroneControl__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
quadrotor_msgs__msg__DroneControl__Sequence__init(quadrotor_msgs__msg__DroneControl__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  quadrotor_msgs__msg__DroneControl * data = NULL;

  if (size) {
    data = (quadrotor_msgs__msg__DroneControl *)allocator.zero_allocate(size, sizeof(quadrotor_msgs__msg__DroneControl), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = quadrotor_msgs__msg__DroneControl__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        quadrotor_msgs__msg__DroneControl__fini(&data[i - 1]);
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
quadrotor_msgs__msg__DroneControl__Sequence__fini(quadrotor_msgs__msg__DroneControl__Sequence * array)
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
      quadrotor_msgs__msg__DroneControl__fini(&array->data[i]);
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

quadrotor_msgs__msg__DroneControl__Sequence *
quadrotor_msgs__msg__DroneControl__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  quadrotor_msgs__msg__DroneControl__Sequence * array = (quadrotor_msgs__msg__DroneControl__Sequence *)allocator.allocate(sizeof(quadrotor_msgs__msg__DroneControl__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = quadrotor_msgs__msg__DroneControl__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
quadrotor_msgs__msg__DroneControl__Sequence__destroy(quadrotor_msgs__msg__DroneControl__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    quadrotor_msgs__msg__DroneControl__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
quadrotor_msgs__msg__DroneControl__Sequence__are_equal(const quadrotor_msgs__msg__DroneControl__Sequence * lhs, const quadrotor_msgs__msg__DroneControl__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!quadrotor_msgs__msg__DroneControl__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
quadrotor_msgs__msg__DroneControl__Sequence__copy(
  const quadrotor_msgs__msg__DroneControl__Sequence * input,
  quadrotor_msgs__msg__DroneControl__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(quadrotor_msgs__msg__DroneControl);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    quadrotor_msgs__msg__DroneControl * data =
      (quadrotor_msgs__msg__DroneControl *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!quadrotor_msgs__msg__DroneControl__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          quadrotor_msgs__msg__DroneControl__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!quadrotor_msgs__msg__DroneControl__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
