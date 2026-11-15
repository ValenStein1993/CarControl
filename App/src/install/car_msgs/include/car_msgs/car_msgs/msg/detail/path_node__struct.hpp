// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from car_msgs:msg/PathNode.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/path_node.hpp"


#ifndef CAR_MSGS__MSG__DETAIL__PATH_NODE__STRUCT_HPP_
#define CAR_MSGS__MSG__DETAIL__PATH_NODE__STRUCT_HPP_

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
# define DEPRECATED__car_msgs__msg__PathNode __attribute__((deprecated))
#else
# define DEPRECATED__car_msgs__msg__PathNode __declspec(deprecated)
#endif

namespace car_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PathNode_
{
  using Type = PathNode_<ContainerAllocator>;

  explicit PathNode_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x = 0.0f;
      this->y = 0.0f;
      this->th = 0.0f;
      this->idx = 0l;
    }
  }

  explicit PathNode_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x = 0.0f;
      this->y = 0.0f;
      this->th = 0.0f;
      this->idx = 0l;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _x_type =
    float;
  _x_type x;
  using _y_type =
    float;
  _y_type y;
  using _th_type =
    float;
  _th_type th;
  using _idx_type =
    int32_t;
  _idx_type idx;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__x(
    const float & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const float & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__th(
    const float & _arg)
  {
    this->th = _arg;
    return *this;
  }
  Type & set__idx(
    const int32_t & _arg)
  {
    this->idx = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    car_msgs::msg::PathNode_<ContainerAllocator> *;
  using ConstRawPtr =
    const car_msgs::msg::PathNode_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<car_msgs::msg::PathNode_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<car_msgs::msg::PathNode_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      car_msgs::msg::PathNode_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<car_msgs::msg::PathNode_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      car_msgs::msg::PathNode_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<car_msgs::msg::PathNode_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<car_msgs::msg::PathNode_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<car_msgs::msg::PathNode_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__car_msgs__msg__PathNode
    std::shared_ptr<car_msgs::msg::PathNode_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__car_msgs__msg__PathNode
    std::shared_ptr<car_msgs::msg::PathNode_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PathNode_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->th != other.th) {
      return false;
    }
    if (this->idx != other.idx) {
      return false;
    }
    return true;
  }
  bool operator!=(const PathNode_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PathNode_

// alias to use template instance with default allocator
using PathNode =
  car_msgs::msg::PathNode_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace car_msgs

#endif  // CAR_MSGS__MSG__DETAIL__PATH_NODE__STRUCT_HPP_
