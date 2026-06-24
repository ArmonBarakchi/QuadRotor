// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from quadrotor_msgs:msg/TrajectoryPoint.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "quadrotor_msgs/msg/trajectory_point.hpp"


#ifndef QUADROTOR_MSGS__MSG__DETAIL__TRAJECTORY_POINT__BUILDER_HPP_
#define QUADROTOR_MSGS__MSG__DETAIL__TRAJECTORY_POINT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "quadrotor_msgs/msg/detail/trajectory_point__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace quadrotor_msgs
{

namespace msg
{

namespace builder
{

class Init_TrajectoryPoint_path_name
{
public:
  explicit Init_TrajectoryPoint_path_name(::quadrotor_msgs::msg::TrajectoryPoint & msg)
  : msg_(msg)
  {}
  ::quadrotor_msgs::msg::TrajectoryPoint path_name(::quadrotor_msgs::msg::TrajectoryPoint::_path_name_type arg)
  {
    msg_.path_name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::quadrotor_msgs::msg::TrajectoryPoint msg_;
};

class Init_TrajectoryPoint_yaw
{
public:
  explicit Init_TrajectoryPoint_yaw(::quadrotor_msgs::msg::TrajectoryPoint & msg)
  : msg_(msg)
  {}
  Init_TrajectoryPoint_path_name yaw(::quadrotor_msgs::msg::TrajectoryPoint::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return Init_TrajectoryPoint_path_name(msg_);
  }

private:
  ::quadrotor_msgs::msg::TrajectoryPoint msg_;
};

class Init_TrajectoryPoint_acceleration
{
public:
  explicit Init_TrajectoryPoint_acceleration(::quadrotor_msgs::msg::TrajectoryPoint & msg)
  : msg_(msg)
  {}
  Init_TrajectoryPoint_yaw acceleration(::quadrotor_msgs::msg::TrajectoryPoint::_acceleration_type arg)
  {
    msg_.acceleration = std::move(arg);
    return Init_TrajectoryPoint_yaw(msg_);
  }

private:
  ::quadrotor_msgs::msg::TrajectoryPoint msg_;
};

class Init_TrajectoryPoint_velocity
{
public:
  explicit Init_TrajectoryPoint_velocity(::quadrotor_msgs::msg::TrajectoryPoint & msg)
  : msg_(msg)
  {}
  Init_TrajectoryPoint_acceleration velocity(::quadrotor_msgs::msg::TrajectoryPoint::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_TrajectoryPoint_acceleration(msg_);
  }

private:
  ::quadrotor_msgs::msg::TrajectoryPoint msg_;
};

class Init_TrajectoryPoint_position
{
public:
  explicit Init_TrajectoryPoint_position(::quadrotor_msgs::msg::TrajectoryPoint & msg)
  : msg_(msg)
  {}
  Init_TrajectoryPoint_velocity position(::quadrotor_msgs::msg::TrajectoryPoint::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_TrajectoryPoint_velocity(msg_);
  }

private:
  ::quadrotor_msgs::msg::TrajectoryPoint msg_;
};

class Init_TrajectoryPoint_header
{
public:
  Init_TrajectoryPoint_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TrajectoryPoint_position header(::quadrotor_msgs::msg::TrajectoryPoint::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_TrajectoryPoint_position(msg_);
  }

private:
  ::quadrotor_msgs::msg::TrajectoryPoint msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::quadrotor_msgs::msg::TrajectoryPoint>()
{
  return quadrotor_msgs::msg::builder::Init_TrajectoryPoint_header();
}

}  // namespace quadrotor_msgs

#endif  // QUADROTOR_MSGS__MSG__DETAIL__TRAJECTORY_POINT__BUILDER_HPP_
