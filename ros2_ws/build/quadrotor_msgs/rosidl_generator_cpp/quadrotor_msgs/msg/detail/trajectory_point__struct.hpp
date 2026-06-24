// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from quadrotor_msgs:msg/TrajectoryPoint.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "quadrotor_msgs/msg/trajectory_point.hpp"


#ifndef QUADROTOR_MSGS__MSG__DETAIL__TRAJECTORY_POINT__STRUCT_HPP_
#define QUADROTOR_MSGS__MSG__DETAIL__TRAJECTORY_POINT__STRUCT_HPP_

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
# define DEPRECATED__quadrotor_msgs__msg__TrajectoryPoint __attribute__((deprecated))
#else
# define DEPRECATED__quadrotor_msgs__msg__TrajectoryPoint __declspec(deprecated)
#endif

namespace quadrotor_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TrajectoryPoint_
{
  using Type = TrajectoryPoint_<ContainerAllocator>;

  explicit TrajectoryPoint_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<double, 3>::iterator, double>(this->position.begin(), this->position.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->velocity.begin(), this->velocity.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->acceleration.begin(), this->acceleration.end(), 0.0);
      this->yaw = 0.0;
      this->path_name = "";
    }
  }

  explicit TrajectoryPoint_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    position(_alloc),
    velocity(_alloc),
    acceleration(_alloc),
    path_name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<double, 3>::iterator, double>(this->position.begin(), this->position.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->velocity.begin(), this->velocity.end(), 0.0);
      std::fill<typename std::array<double, 3>::iterator, double>(this->acceleration.begin(), this->acceleration.end(), 0.0);
      this->yaw = 0.0;
      this->path_name = "";
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
  using _acceleration_type =
    std::array<double, 3>;
  _acceleration_type acceleration;
  using _yaw_type =
    double;
  _yaw_type yaw;
  using _path_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _path_name_type path_name;

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
  Type & set__acceleration(
    const std::array<double, 3> & _arg)
  {
    this->acceleration = _arg;
    return *this;
  }
  Type & set__yaw(
    const double & _arg)
  {
    this->yaw = _arg;
    return *this;
  }
  Type & set__path_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->path_name = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    quadrotor_msgs::msg::TrajectoryPoint_<ContainerAllocator> *;
  using ConstRawPtr =
    const quadrotor_msgs::msg::TrajectoryPoint_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<quadrotor_msgs::msg::TrajectoryPoint_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<quadrotor_msgs::msg::TrajectoryPoint_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      quadrotor_msgs::msg::TrajectoryPoint_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<quadrotor_msgs::msg::TrajectoryPoint_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      quadrotor_msgs::msg::TrajectoryPoint_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<quadrotor_msgs::msg::TrajectoryPoint_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<quadrotor_msgs::msg::TrajectoryPoint_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<quadrotor_msgs::msg::TrajectoryPoint_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__quadrotor_msgs__msg__TrajectoryPoint
    std::shared_ptr<quadrotor_msgs::msg::TrajectoryPoint_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__quadrotor_msgs__msg__TrajectoryPoint
    std::shared_ptr<quadrotor_msgs::msg::TrajectoryPoint_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TrajectoryPoint_ & other) const
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
    if (this->acceleration != other.acceleration) {
      return false;
    }
    if (this->yaw != other.yaw) {
      return false;
    }
    if (this->path_name != other.path_name) {
      return false;
    }
    return true;
  }
  bool operator!=(const TrajectoryPoint_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TrajectoryPoint_

// alias to use template instance with default allocator
using TrajectoryPoint =
  quadrotor_msgs::msg::TrajectoryPoint_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace quadrotor_msgs

#endif  // QUADROTOR_MSGS__MSG__DETAIL__TRAJECTORY_POINT__STRUCT_HPP_
