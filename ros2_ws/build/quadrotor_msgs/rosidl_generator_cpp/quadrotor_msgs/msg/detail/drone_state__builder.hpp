// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from quadrotor_msgs:msg/DroneState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "quadrotor_msgs/msg/drone_state.hpp"


#ifndef QUADROTOR_MSGS__MSG__DETAIL__DRONE_STATE__BUILDER_HPP_
#define QUADROTOR_MSGS__MSG__DETAIL__DRONE_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "quadrotor_msgs/msg/detail/drone_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace quadrotor_msgs
{

namespace msg
{

namespace builder
{

class Init_DroneState_accel_bias
{
public:
  explicit Init_DroneState_accel_bias(::quadrotor_msgs::msg::DroneState & msg)
  : msg_(msg)
  {}
  ::quadrotor_msgs::msg::DroneState accel_bias(::quadrotor_msgs::msg::DroneState::_accel_bias_type arg)
  {
    msg_.accel_bias = std::move(arg);
    return std::move(msg_);
  }

private:
  ::quadrotor_msgs::msg::DroneState msg_;
};

class Init_DroneState_gyro_bias
{
public:
  explicit Init_DroneState_gyro_bias(::quadrotor_msgs::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_accel_bias gyro_bias(::quadrotor_msgs::msg::DroneState::_gyro_bias_type arg)
  {
    msg_.gyro_bias = std::move(arg);
    return Init_DroneState_accel_bias(msg_);
  }

private:
  ::quadrotor_msgs::msg::DroneState msg_;
};

class Init_DroneState_omega
{
public:
  explicit Init_DroneState_omega(::quadrotor_msgs::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_gyro_bias omega(::quadrotor_msgs::msg::DroneState::_omega_type arg)
  {
    msg_.omega = std::move(arg);
    return Init_DroneState_gyro_bias(msg_);
  }

private:
  ::quadrotor_msgs::msg::DroneState msg_;
};

class Init_DroneState_quaternion
{
public:
  explicit Init_DroneState_quaternion(::quadrotor_msgs::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_omega quaternion(::quadrotor_msgs::msg::DroneState::_quaternion_type arg)
  {
    msg_.quaternion = std::move(arg);
    return Init_DroneState_omega(msg_);
  }

private:
  ::quadrotor_msgs::msg::DroneState msg_;
};

class Init_DroneState_velocity
{
public:
  explicit Init_DroneState_velocity(::quadrotor_msgs::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_quaternion velocity(::quadrotor_msgs::msg::DroneState::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_DroneState_quaternion(msg_);
  }

private:
  ::quadrotor_msgs::msg::DroneState msg_;
};

class Init_DroneState_position
{
public:
  explicit Init_DroneState_position(::quadrotor_msgs::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_velocity position(::quadrotor_msgs::msg::DroneState::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_DroneState_velocity(msg_);
  }

private:
  ::quadrotor_msgs::msg::DroneState msg_;
};

class Init_DroneState_header
{
public:
  Init_DroneState_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DroneState_position header(::quadrotor_msgs::msg::DroneState::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_DroneState_position(msg_);
  }

private:
  ::quadrotor_msgs::msg::DroneState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::quadrotor_msgs::msg::DroneState>()
{
  return quadrotor_msgs::msg::builder::Init_DroneState_header();
}

}  // namespace quadrotor_msgs

#endif  // QUADROTOR_MSGS__MSG__DETAIL__DRONE_STATE__BUILDER_HPP_
