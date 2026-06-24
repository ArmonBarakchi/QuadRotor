// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from quadrotor_msgs:msg/DroneState.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "quadrotor_msgs/msg/detail/drone_state__rosidl_typesupport_introspection_c.h"
#include "quadrotor_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "quadrotor_msgs/msg/detail/drone_state__functions.h"
#include "quadrotor_msgs/msg/detail/drone_state__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__DroneState_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  quadrotor_msgs__msg__DroneState__init(message_memory);
}

void quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__DroneState_fini_function(void * message_memory)
{
  quadrotor_msgs__msg__DroneState__fini(message_memory);
}

size_t quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__size_function__DroneState__position(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_const_function__DroneState__position(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_function__DroneState__position(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__fetch_function__DroneState__position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_const_function__DroneState__position(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__assign_function__DroneState__position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_function__DroneState__position(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

size_t quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__size_function__DroneState__velocity(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_const_function__DroneState__velocity(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_function__DroneState__velocity(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__fetch_function__DroneState__velocity(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_const_function__DroneState__velocity(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__assign_function__DroneState__velocity(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_function__DroneState__velocity(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

size_t quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__size_function__DroneState__quaternion(
  const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_const_function__DroneState__quaternion(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_function__DroneState__quaternion(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__fetch_function__DroneState__quaternion(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_const_function__DroneState__quaternion(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__assign_function__DroneState__quaternion(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_function__DroneState__quaternion(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

size_t quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__size_function__DroneState__omega(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_const_function__DroneState__omega(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_function__DroneState__omega(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__fetch_function__DroneState__omega(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_const_function__DroneState__omega(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__assign_function__DroneState__omega(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_function__DroneState__omega(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

size_t quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__size_function__DroneState__gyro_bias(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_const_function__DroneState__gyro_bias(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_function__DroneState__gyro_bias(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__fetch_function__DroneState__gyro_bias(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_const_function__DroneState__gyro_bias(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__assign_function__DroneState__gyro_bias(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_function__DroneState__gyro_bias(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

size_t quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__size_function__DroneState__accel_bias(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_const_function__DroneState__accel_bias(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_function__DroneState__accel_bias(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__fetch_function__DroneState__accel_bias(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_const_function__DroneState__accel_bias(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__assign_function__DroneState__accel_bias(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_function__DroneState__accel_bias(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__DroneState_message_member_array[7] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(quadrotor_msgs__msg__DroneState, header),  // bytes offset in struct
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
    offsetof(quadrotor_msgs__msg__DroneState, position),  // bytes offset in struct
    NULL,  // default value
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__size_function__DroneState__position,  // size() function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_const_function__DroneState__position,  // get_const(index) function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_function__DroneState__position,  // get(index) function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__fetch_function__DroneState__position,  // fetch(index, &value) function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__assign_function__DroneState__position,  // assign(index, value) function pointer
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
    offsetof(quadrotor_msgs__msg__DroneState, velocity),  // bytes offset in struct
    NULL,  // default value
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__size_function__DroneState__velocity,  // size() function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_const_function__DroneState__velocity,  // get_const(index) function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_function__DroneState__velocity,  // get(index) function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__fetch_function__DroneState__velocity,  // fetch(index, &value) function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__assign_function__DroneState__velocity,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "quaternion",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(quadrotor_msgs__msg__DroneState, quaternion),  // bytes offset in struct
    NULL,  // default value
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__size_function__DroneState__quaternion,  // size() function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_const_function__DroneState__quaternion,  // get_const(index) function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_function__DroneState__quaternion,  // get(index) function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__fetch_function__DroneState__quaternion,  // fetch(index, &value) function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__assign_function__DroneState__quaternion,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "omega",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(quadrotor_msgs__msg__DroneState, omega),  // bytes offset in struct
    NULL,  // default value
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__size_function__DroneState__omega,  // size() function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_const_function__DroneState__omega,  // get_const(index) function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_function__DroneState__omega,  // get(index) function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__fetch_function__DroneState__omega,  // fetch(index, &value) function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__assign_function__DroneState__omega,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "gyro_bias",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(quadrotor_msgs__msg__DroneState, gyro_bias),  // bytes offset in struct
    NULL,  // default value
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__size_function__DroneState__gyro_bias,  // size() function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_const_function__DroneState__gyro_bias,  // get_const(index) function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_function__DroneState__gyro_bias,  // get(index) function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__fetch_function__DroneState__gyro_bias,  // fetch(index, &value) function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__assign_function__DroneState__gyro_bias,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "accel_bias",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(quadrotor_msgs__msg__DroneState, accel_bias),  // bytes offset in struct
    NULL,  // default value
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__size_function__DroneState__accel_bias,  // size() function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_const_function__DroneState__accel_bias,  // get_const(index) function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__get_function__DroneState__accel_bias,  // get(index) function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__fetch_function__DroneState__accel_bias,  // fetch(index, &value) function pointer
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__assign_function__DroneState__accel_bias,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__DroneState_message_members = {
  "quadrotor_msgs__msg",  // message namespace
  "DroneState",  // message name
  7,  // number of fields
  sizeof(quadrotor_msgs__msg__DroneState),
  false,  // has_any_key_member_
  quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__DroneState_message_member_array,  // message members
  quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__DroneState_init_function,  // function to initialize message memory (memory has to be allocated)
  quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__DroneState_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__DroneState_message_type_support_handle = {
  0,
  &quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__DroneState_message_members,
  get_message_typesupport_handle_function,
  &quadrotor_msgs__msg__DroneState__get_type_hash,
  &quadrotor_msgs__msg__DroneState__get_type_description,
  &quadrotor_msgs__msg__DroneState__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_quadrotor_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, quadrotor_msgs, msg, DroneState)() {
  quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__DroneState_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__DroneState_message_type_support_handle.typesupport_identifier) {
    quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__DroneState_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &quadrotor_msgs__msg__DroneState__rosidl_typesupport_introspection_c__DroneState_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
