// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from quadrotor_msgs:msg/TrajectoryPoint.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "quadrotor_msgs/msg/detail/trajectory_point__rosidl_typesupport_introspection_c.h"
#include "quadrotor_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "quadrotor_msgs/msg/detail/trajectory_point__functions.h"
#include "quadrotor_msgs/msg/detail/trajectory_point__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `path_name`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__TrajectoryPoint_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  quadrotor_msgs__msg__TrajectoryPoint__init(message_memory);
}

void quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__TrajectoryPoint_fini_function(void * message_memory)
{
  quadrotor_msgs__msg__TrajectoryPoint__fini(message_memory);
}

size_t quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__size_function__TrajectoryPoint__position(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__get_const_function__TrajectoryPoint__position(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__get_function__TrajectoryPoint__position(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__fetch_function__TrajectoryPoint__position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__get_const_function__TrajectoryPoint__position(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__assign_function__TrajectoryPoint__position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__get_function__TrajectoryPoint__position(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

size_t quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__size_function__TrajectoryPoint__velocity(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__get_const_function__TrajectoryPoint__velocity(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__get_function__TrajectoryPoint__velocity(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__fetch_function__TrajectoryPoint__velocity(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__get_const_function__TrajectoryPoint__velocity(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__assign_function__TrajectoryPoint__velocity(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__get_function__TrajectoryPoint__velocity(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

size_t quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__size_function__TrajectoryPoint__acceleration(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__get_const_function__TrajectoryPoint__acceleration(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__get_function__TrajectoryPoint__acceleration(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__fetch_function__TrajectoryPoint__acceleration(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__get_const_function__TrajectoryPoint__acceleration(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__assign_function__TrajectoryPoint__acceleration(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__get_function__TrajectoryPoint__acceleration(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__TrajectoryPoint_message_member_array[6] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(quadrotor_msgs__msg__TrajectoryPoint, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(quadrotor_msgs__msg__TrajectoryPoint, position),  // bytes offset in struct
    NULL,  // default value
    quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__size_function__TrajectoryPoint__position,  // size() function pointer
    quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__get_const_function__TrajectoryPoint__position,  // get_const(index) function pointer
    quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__get_function__TrajectoryPoint__position,  // get(index) function pointer
    quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__fetch_function__TrajectoryPoint__position,  // fetch(index, &value) function pointer
    quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__assign_function__TrajectoryPoint__position,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "velocity",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(quadrotor_msgs__msg__TrajectoryPoint, velocity),  // bytes offset in struct
    NULL,  // default value
    quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__size_function__TrajectoryPoint__velocity,  // size() function pointer
    quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__get_const_function__TrajectoryPoint__velocity,  // get_const(index) function pointer
    quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__get_function__TrajectoryPoint__velocity,  // get(index) function pointer
    quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__fetch_function__TrajectoryPoint__velocity,  // fetch(index, &value) function pointer
    quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__assign_function__TrajectoryPoint__velocity,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "acceleration",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(quadrotor_msgs__msg__TrajectoryPoint, acceleration),  // bytes offset in struct
    NULL,  // default value
    quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__size_function__TrajectoryPoint__acceleration,  // size() function pointer
    quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__get_const_function__TrajectoryPoint__acceleration,  // get_const(index) function pointer
    quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__get_function__TrajectoryPoint__acceleration,  // get(index) function pointer
    quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__fetch_function__TrajectoryPoint__acceleration,  // fetch(index, &value) function pointer
    quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__assign_function__TrajectoryPoint__acceleration,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "yaw",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(quadrotor_msgs__msg__TrajectoryPoint, yaw),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "path_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(quadrotor_msgs__msg__TrajectoryPoint, path_name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__TrajectoryPoint_message_members = {
  "quadrotor_msgs__msg",  // message namespace
  "TrajectoryPoint",  // message name
  6,  // number of fields
  sizeof(quadrotor_msgs__msg__TrajectoryPoint),
  false,  // has_any_key_member_
  quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__TrajectoryPoint_message_member_array,  // message members
  quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__TrajectoryPoint_init_function,  // function to initialize message memory (memory has to be allocated)
  quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__TrajectoryPoint_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__TrajectoryPoint_message_type_support_handle = {
  0,
  &quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__TrajectoryPoint_message_members,
  get_message_typesupport_handle_function,
  &quadrotor_msgs__msg__TrajectoryPoint__get_type_hash,
  &quadrotor_msgs__msg__TrajectoryPoint__get_type_description,
  &quadrotor_msgs__msg__TrajectoryPoint__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_quadrotor_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, quadrotor_msgs, msg, TrajectoryPoint)() {
  quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__TrajectoryPoint_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__TrajectoryPoint_message_type_support_handle.typesupport_identifier) {
    quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__TrajectoryPoint_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &quadrotor_msgs__msg__TrajectoryPoint__rosidl_typesupport_introspection_c__TrajectoryPoint_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
