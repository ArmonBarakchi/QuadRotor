// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from quadrotor_msgs:msg/TrajectoryPoint.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "quadrotor_msgs/msg/trajectory_point.h"


#ifndef QUADROTOR_MSGS__MSG__DETAIL__TRAJECTORY_POINT__STRUCT_H_
#define QUADROTOR_MSGS__MSG__DETAIL__TRAJECTORY_POINT__STRUCT_H_

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
// Member 'path_name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/TrajectoryPoint in the package quadrotor_msgs.
typedef struct quadrotor_msgs__msg__TrajectoryPoint
{
  std_msgs__msg__Header header;
  double position[3];
  double velocity[3];
  double acceleration[3];
  double yaw;
  rosidl_runtime_c__String path_name;
} quadrotor_msgs__msg__TrajectoryPoint;

// Struct for a sequence of quadrotor_msgs__msg__TrajectoryPoint.
typedef struct quadrotor_msgs__msg__TrajectoryPoint__Sequence
{
  quadrotor_msgs__msg__TrajectoryPoint * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} quadrotor_msgs__msg__TrajectoryPoint__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // QUADROTOR_MSGS__MSG__DETAIL__TRAJECTORY_POINT__STRUCT_H_
