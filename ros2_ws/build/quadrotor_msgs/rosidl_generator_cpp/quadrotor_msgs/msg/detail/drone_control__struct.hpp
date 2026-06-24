// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from quadrotor_msgs:msg/DroneControl.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "quadrotor_msgs/msg/drone_control.hpp"


#ifndef QUADROTOR_MSGS__MSG__DETAIL__DRONE_CONTROL__STRUCT_HPP_
#define QUADROTOR_MSGS__MSG__DETAIL__DRONE_CONTROL__STRUCT_HPP_

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
# define DEPRECATED__quadrotor_msgs__msg__DroneControl __attribute__((deprecated))
#else
# define DEPRECATED__quadrotor_msgs__msg__DroneControl __declspec(deprecated)
#endif

namespace quadrotor_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DroneControl_
{
  using Type = DroneControl_<ContainerAllocator>;

  explicit DroneControl_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<double, 3>::iterator, double>(this->force_des.begin(), this->force_des.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->torque.begin(), this->torque.end(), 0.0);
    }
  }

  explicit DroneControl_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    force_des(_alloc),
    torque(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<double, 3>::iterator, double>(this->force_des.begin(), this->force_des.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->torque.begin(), this->torque.end(), 0.0);
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _force_des_type =
    std::array<double, 3>;
  _force_des_type force_des;
  using _torque_type =
    std::array<double, 3>;
  _torque_type torque;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__force_des(
    const std::array<double, 3> & _arg)
  {
    this->force_des = _arg;
    return *this;
  }
  Type & set__torque(
    const std::array<double, 3> & _arg)
  {
    this->torque = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    quadrotor_msgs::msg::DroneControl_<ContainerAllocator> *;
  using ConstRawPtr =
    const quadrotor_msgs::msg::DroneControl_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<quadrotor_msgs::msg::DroneControl_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<quadrotor_msgs::msg::DroneControl_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      quadrotor_msgs::msg::DroneControl_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<quadrotor_msgs::msg::DroneControl_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      quadrotor_msgs::msg::DroneControl_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<quadrotor_msgs::msg::DroneControl_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<quadrotor_msgs::msg::DroneControl_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<quadrotor_msgs::msg::DroneControl_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__quadrotor_msgs__msg__DroneControl
    std::shared_ptr<quadrotor_msgs::msg::DroneControl_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__quadrotor_msgs__msg__DroneControl
    std::shared_ptr<quadrotor_msgs::msg::DroneControl_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DroneControl_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->force_des != other.force_des) {
      return false;
    }
    if (this->torque != other.torque) {
      return false;
    }
    return true;
  }
  bool operator!=(const DroneControl_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DroneControl_

// alias to use template instance with default allocator
using DroneControl =
  quadrotor_msgs::msg::DroneControl_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace quadrotor_msgs

#endif  // QUADROTOR_MSGS__MSG__DETAIL__DRONE_CONTROL__STRUCT_HPP_
