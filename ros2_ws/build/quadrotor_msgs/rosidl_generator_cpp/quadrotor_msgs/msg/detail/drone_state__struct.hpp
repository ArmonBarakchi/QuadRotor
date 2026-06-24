// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from quadrotor_msgs:msg/DroneState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "quadrotor_msgs/msg/drone_state.hpp"


#ifndef QUADROTOR_MSGS__MSG__DETAIL__DRONE_STATE__STRUCT_HPP_
#define QUADROTOR_MSGS__MSG__DETAIL__DRONE_STATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__quadrotor_msgs__msg__DroneState __attribute__((deprecated))
#else
# define DEPRECATED__quadrotor_msgs__msg__DroneState __declspec(deprecated)
#endif

namespace quadrotor_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DroneState_
{
  using Type = DroneState_<ContainerAllocator>;

  explicit DroneState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<double, 3>::iterator, double>(this->position.begin(), this->position.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->velocity.begin(), this->velocity.end(), 0.0);
      std::fill<typename std::array<double, 4>::iterator, double>(this->quaternion.begin(), this->quaternion.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->omega.begin(), this->omega.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->gyro_bias.begin(), this->gyro_bias.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->accel_bias.begin(), this->accel_bias.end(), 0.0);
    }
  }

  explicit DroneState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    position(_alloc),
    velocity(_alloc),
    quaternion(_alloc),
    omega(_alloc),
    gyro_bias(_alloc),
    accel_bias(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<double, 3>::iterator, double>(this->position.begin(), this->position.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->velocity.begin(), this->velocity.end(), 0.0);
      std::fill<typename std::array<double, 4>::iterator, double>(this->quaternion.begin(), this->quaternion.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->omega.begin(), this->omega.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->gyro_bias.begin(), this->gyro_bias.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->accel_bias.begin(), this->accel_bias.end(), 0.0);
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _position_type =
    std::array<double, 3>;
  _position_type position;
  using _velocity_type =
    std::array<double, 3>;
  _velocity_type velocity;
  using _quaternion_type =
    std::array<double, 4>;
  _quaternion_type quaternion;
  using _omega_type =
    std::array<double, 3>;
  _omega_type omega;
  using _gyro_bias_type =
    std::array<double, 3>;
  _gyro_bias_type gyro_bias;
  using _accel_bias_type =
    std::array<double, 3>;
  _accel_bias_type accel_bias;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__position(
    const std::array<double, 3> & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__velocity(
    const std::array<double, 3> & _arg)
  {
    this->velocity = _arg;
    return *this;
  }
  Type & set__quaternion(
    const std::array<double, 4> & _arg)
  {
    this->quaternion = _arg;
    return *this;
  }
  Type & set__omega(
    const std::array<double, 3> & _arg)
  {
    this->omega = _arg;
    return *this;
  }
  Type & set__gyro_bias(
    const std::array<double, 3> & _arg)
  {
    this->gyro_bias = _arg;
    return *this;
  }
  Type & set__accel_bias(
    const std::array<double, 3> & _arg)
  {
    this->accel_bias = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    quadrotor_msgs::msg::DroneState_<ContainerAllocator> *;
  using ConstRawPtr =
    const quadrotor_msgs::msg::DroneState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<quadrotor_msgs::msg::DroneState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<quadrotor_msgs::msg::DroneState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      quadrotor_msgs::msg::DroneState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<quadrotor_msgs::msg::DroneState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      quadrotor_msgs::msg::DroneState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<quadrotor_msgs::msg::DroneState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<quadrotor_msgs::msg::DroneState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<quadrotor_msgs::msg::DroneState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__quadrotor_msgs__msg__DroneState
    std::shared_ptr<quadrotor_msgs::msg::DroneState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__quadrotor_msgs__msg__DroneState
    std::shared_ptr<quadrotor_msgs::msg::DroneState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DroneState_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->velocity != other.velocity) {
      return false;
    }
    if (this->quaternion != other.quaternion) {
      return false;
    }
    if (this->omega != other.omega) {
      return false;
    }
    if (this->gyro_bias != other.gyro_bias) {
      return false;
    }
    if (this->accel_bias != other.accel_bias) {
      return false;
    }
    return true;
  }
  bool operator!=(const DroneState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DroneState_

// alias to use template instance with default allocator
using DroneState =
  quadrotor_msgs::msg::DroneState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace quadrotor_msgs

#endif  // QUADROTOR_MSGS__MSG__DETAIL__DRONE_STATE__STRUCT_HPP_
