// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from quadrotor_msgs:msg/DroneControl.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "quadrotor_msgs/msg/drone_control.hpp"


#ifndef QUADROTOR_MSGS__MSG__DETAIL__DRONE_CONTROL__BUILDER_HPP_
#define QUADROTOR_MSGS__MSG__DETAIL__DRONE_CONTROL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "quadrotor_msgs/msg/detail/drone_control__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace quadrotor_msgs
{

namespace msg
{

namespace builder
{

class Init_DroneControl_torque
{
public:
  explicit Init_DroneControl_torque(::quadrotor_msgs::msg::DroneControl & msg)
  : msg_(msg)
  {}
  ::quadrotor_msgs::msg::DroneControl torque(::quadrotor_msgs::msg::DroneControl::_torque_type arg)
  {
    msg_.torque = std::move(arg);
    return std::move(msg_);
  }

private:
  ::quadrotor_msgs::msg::DroneControl msg_;
};

class Init_DroneControl_force_des
{
public:
  explicit Init_DroneControl_force_des(::quadrotor_msgs::msg::DroneControl & msg)
  : msg_(msg)
  {}
  Init_DroneControl_torque force_des(::quadrotor_msgs::msg::DroneControl::_force_des_type arg)
  {
    msg_.force_des = std::move(arg);
    return Init_DroneControl_torque(msg_);
  }

private:
  ::quadrotor_msgs::msg::DroneControl msg_;
};

class Init_DroneControl_header
{
public:
  Init_DroneControl_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DroneControl_force_des header(::quadrotor_msgs::msg::DroneControl::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_DroneControl_force_des(msg_);
  }

private:
  ::quadrotor_msgs::msg::DroneControl msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::quadrotor_msgs::msg::DroneControl>()
{
  return quadrotor_msgs::msg::builder::Init_DroneControl_header();
}

}  // namespace quadrotor_msgs

#endif  // QUADROTOR_MSGS__MSG__DETAIL__DRONE_CONTROL__BUILDER_HPP_
