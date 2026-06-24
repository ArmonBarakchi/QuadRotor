// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from quadrotor_msgs:msg/DroneState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "quadrotor_msgs/msg/drone_state.h"


#ifndef QUADROTOR_MSGS__MSG__DETAIL__DRONE_STATE__STRUCT_H_
#define QUADROTOR_MSGS__MSG__DETAIL__DRONE_STATE__STRUCT_H_

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

/// Struct defined in msg/DroneState in the package quadrotor_msgs.
typedef struct quadrotor_msgs__msg__DroneState
{
  std_msgs__msg__Header header;
  double position[3];
  double velocity[3];
  double quaternion[4];
  double omega[3];
  double gyro_bias[3];
  double accel_bias[3];
} quadrotor_msgs__msg__DroneState;

// Struct for a sequence of quadrotor_msgs__msg__DroneState.
typedef struct quadrotor_msgs__msg__DroneState__Sequence
{
  quadrotor_msgs__msg__DroneState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} quadrotor_msgs__msg__DroneState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // QUADROTOR_MSGS__MSG__DETAIL__DRONE_STATE__STRUCT_H_
