// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from car_msgs:msg/NodeState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/node_state.hpp"


#ifndef CAR_MSGS__MSG__DETAIL__NODE_STATE__STRUCT_HPP_
#define CAR_MSGS__MSG__DETAIL__NODE_STATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__car_msgs__msg__NodeState __attribute__((deprecated))
#else
# define DEPRECATED__car_msgs__msg__NodeState __declspec(deprecated)
#endif

namespace car_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct NodeState_
{
  using Type = NodeState_<ContainerAllocator>;

  explicit NodeState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->localizer_is_ready = false;
    }
  }

  explicit NodeState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->localizer_is_ready = false;
    }
  }

  // field types and members
  using _localizer_is_ready_type =
    bool;
  _localizer_is_ready_type localizer_is_ready;

  // setters for named parameter idiom
  Type & set__localizer_is_ready(
    const bool & _arg)
  {
    this->localizer_is_ready = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    car_msgs::msg::NodeState_<ContainerAllocator> *;
  using ConstRawPtr =
    const car_msgs::msg::NodeState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<car_msgs::msg::NodeState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<car_msgs::msg::NodeState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      car_msgs::msg::NodeState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<car_msgs::msg::NodeState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      car_msgs::msg::NodeState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<car_msgs::msg::NodeState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<car_msgs::msg::NodeState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<car_msgs::msg::NodeState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__car_msgs__msg__NodeState
    std::shared_ptr<car_msgs::msg::NodeState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__car_msgs__msg__NodeState
    std::shared_ptr<car_msgs::msg::NodeState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const NodeState_ & other) const
  {
    if (this->localizer_is_ready != other.localizer_is_ready) {
      return false;
    }
    return true;
  }
  bool operator!=(const NodeState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct NodeState_

// alias to use template instance with default allocator
using NodeState =
  car_msgs::msg::NodeState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace car_msgs

#endif  // CAR_MSGS__MSG__DETAIL__NODE_STATE__STRUCT_HPP_
