// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from quadrotor_msgs:msg/DroneState.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "quadrotor_msgs/msg/detail/drone_state__functions.h"
#include "quadrotor_msgs/msg/detail/drone_state__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace quadrotor_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void DroneState_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) quadrotor_msgs::msg::DroneState(_init);
}

void DroneState_fini_function(void * message_memory)
{
  auto typed_message = static_cast<quadrotor_msgs::msg::DroneState *>(message_memory);
  typed_message->~DroneState();
}

size_t size_function__DroneState__position(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__DroneState__position(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<double, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__DroneState__position(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<double, 3> *>(untyped_member);
  return &member[index];
}

void fetch_function__DroneState__position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__DroneState__position(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__DroneState__position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__DroneState__position(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

size_t size_function__DroneState__velocity(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__DroneState__velocity(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<double, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__DroneState__velocity(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<double, 3> *>(untyped_member);
  return &member[index];
}

void fetch_function__DroneState__velocity(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__DroneState__velocity(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__DroneState__velocity(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__DroneState__velocity(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

size_t size_function__DroneState__quaternion(const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * get_const_function__DroneState__quaternion(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<double, 4> *>(untyped_member);
  return &member[index];
}

void * get_function__DroneState__quaternion(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<double, 4> *>(untyped_member);
  return &member[index];
}

void fetch_function__DroneState__quaternion(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__DroneState__quaternion(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__DroneState__quaternion(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__DroneState__quaternion(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

size_t size_function__DroneState__omega(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__DroneState__omega(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<double, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__DroneState__omega(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<double, 3> *>(untyped_member);
  return &member[index];
}

void fetch_function__DroneState__omega(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__DroneState__omega(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__DroneState__omega(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__DroneState__omega(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

size_t size_function__DroneState__gyro_bias(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__DroneState__gyro_bias(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<double, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__DroneState__gyro_bias(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<double, 3> *>(untyped_member);
  return &member[index];
}

void fetch_function__DroneState__gyro_bias(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__DroneState__gyro_bias(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__DroneState__gyro_bias(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__DroneState__gyro_bias(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

size_t size_function__DroneState__accel_bias(const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * get_const_function__DroneState__accel_bias(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<double, 3> *>(untyped_member);
  return &member[index];
}

void * get_function__DroneState__accel_bias(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<double, 3> *>(untyped_member);
  return &member[index];
}

void fetch_function__DroneState__accel_bias(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__DroneState__accel_bias(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__DroneState__accel_bias(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__DroneState__accel_bias(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember DroneState_message_member_array[7] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(quadrotor_msgs::msg::DroneState, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "position",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(quadrotor_msgs::msg::DroneState, position),  // bytes offset in struct
    nullptr,  // default value
    size_function__DroneState__position,  // size() function pointer
    get_const_function__DroneState__position,  // get_const(index) function pointer
    get_function__DroneState__position,  // get(index) function pointer
    fetch_function__DroneState__position,  // fetch(index, &value) function pointer
    assign_function__DroneState__position,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "velocity",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(quadrotor_msgs::msg::DroneState, velocity),  // bytes offset in struct
    nullptr,  // default value
    size_function__DroneState__velocity,  // size() function pointer
    get_const_function__DroneState__velocity,  // get_const(index) function pointer
    get_function__DroneState__velocity,  // get(index) function pointer
    fetch_function__DroneState__velocity,  // fetch(index, &value) function pointer
    assign_function__DroneState__velocity,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "quaternion",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(quadrotor_msgs::msg::DroneState, quaternion),  // bytes offset in struct
    nullptr,  // default value
    size_function__DroneState__quaternion,  // size() function pointer
    get_const_function__DroneState__quaternion,  // get_const(index) function pointer
    get_function__DroneState__quaternion,  // get(index) function pointer
    fetch_function__DroneState__quaternion,  // fetch(index, &value) function pointer
    assign_function__DroneState__quaternion,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "omega",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(quadrotor_msgs::msg::DroneState, omega),  // bytes offset in struct
    nullptr,  // default value
    size_function__DroneState__omega,  // size() function pointer
    get_const_function__DroneState__omega,  // get_const(index) function pointer
    get_function__DroneState__omega,  // get(index) function pointer
    fetch_function__DroneState__omega,  // fetch(index, &value) function pointer
    assign_function__DroneState__omega,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "gyro_bias",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(quadrotor_msgs::msg::DroneState, gyro_bias),  // bytes offset in struct
    nullptr,  // default value
    size_function__DroneState__gyro_bias,  // size() function pointer
    get_const_function__DroneState__gyro_bias,  // get_const(index) function pointer
    get_function__DroneState__gyro_bias,  // get(index) function pointer
    fetch_function__DroneState__gyro_bias,  // fetch(index, &value) function pointer
    assign_function__DroneState__gyro_bias,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "accel_bias",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(quadrotor_msgs::msg::DroneState, accel_bias),  // bytes offset in struct
    nullptr,  // default value
    size_function__DroneState__accel_bias,  // size() function pointer
    get_const_function__DroneState__accel_bias,  // get_const(index) function pointer
    get_function__DroneState__accel_bias,  // get(index) function pointer
    fetch_function__DroneState__accel_bias,  // fetch(index, &value) function pointer
    assign_function__DroneState__accel_bias,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers DroneState_message_members = {
  "quadrotor_msgs::msg",  // message namespace
  "DroneState",  // message name
  7,  // number of fields
  sizeof(quadrotor_msgs::msg::DroneState),
  false,  // has_any_key_member_
  DroneState_message_member_array,  // message members
  DroneState_init_function,  // function to initialize message memory (memory has to be allocated)
  DroneState_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t DroneState_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &DroneState_message_members,
  get_message_typesupport_handle_function,
  &quadrotor_msgs__msg__DroneState__get_type_hash,
  &quadrotor_msgs__msg__DroneState__get_type_description,
  &quadrotor_msgs__msg__DroneState__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace quadrotor_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<quadrotor_msgs::msg::DroneState>()
{
  return &::quadrotor_msgs::msg::rosidl_typesupport_introspection_cpp::DroneState_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, quadrotor_msgs, msg, DroneState)() {
  return &::quadrotor_msgs::msg::rosidl_typesupport_introspection_cpp::DroneState_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
