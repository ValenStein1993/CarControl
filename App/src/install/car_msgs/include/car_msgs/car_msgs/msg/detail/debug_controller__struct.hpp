// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from car_msgs:msg/DebugController.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/debug_controller.hpp"


#ifndef CAR_MSGS__MSG__DETAIL__DEBUG_CONTROLLER__STRUCT_HPP_
#define CAR_MSGS__MSG__DETAIL__DEBUG_CONTROLLER__STRUCT_HPP_

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
# define DEPRECATED__car_msgs__msg__DebugController __attribute__((deprecated))
#else
# define DEPRECATED__car_msgs__msg__DebugController __declspec(deprecated)
#endif

namespace car_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DebugController_
{
  using Type = DebugController_<ContainerAllocator>;

  explicit DebugController_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->yaw_rate = 0.0f;
      this->yaw = 0.0f;
      this->cn_yaw = 0.0f;
      this->speed = 0.0f;
      this->steering_angle = 0.0f;
      this->pdx_cnode = 0l;
      this->cte = 0.0f;
      this->heading_error = 0.0f;
    }
  }

  explicit DebugController_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->yaw_rate = 0.0f;
      this->yaw = 0.0f;
      this->cn_yaw = 0.0f;
      this->speed = 0.0f;
      this->steering_angle = 0.0f;
      this->pdx_cnode = 0l;
      this->cte = 0.0f;
      this->heading_error = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _yaw_rate_type =
    float;
  _yaw_rate_type yaw_rate;
  using _yaw_type =
    float;
  _yaw_type yaw;
  using _cn_yaw_type =
    float;
  _cn_yaw_type cn_yaw;
  using _speed_type =
    float;
  _speed_type speed;
  using _steering_angle_type =
    float;
  _steering_angle_type steering_angle;
  using _pdx_cnode_type =
    int32_t;
  _pdx_cnode_type pdx_cnode;
  using _cte_type =
    float;
  _cte_type cte;
  using _heading_error_type =
    float;
  _heading_error_type heading_error;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__yaw_rate(
    const float & _arg)
  {
    this->yaw_rate = _arg;
    return *this;
  }
  Type & set__yaw(
    const float & _arg)
  {
    this->yaw = _arg;
    return *this;
  }
  Type & set__cn_yaw(
    const float & _arg)
  {
    this->cn_yaw = _arg;
    return *this;
  }
  Type & set__speed(
    const float & _arg)
  {
    this->speed = _arg;
    return *this;
  }
  Type & set__steering_angle(
    const float & _arg)
  {
    this->steering_angle = _arg;
    return *this;
  }
  Type & set__pdx_cnode(
    const int32_t & _arg)
  {
    this->pdx_cnode = _arg;
    return *this;
  }
  Type & set__cte(
    const float & _arg)
  {
    this->cte = _arg;
    return *this;
  }
  Type & set__heading_error(
    const float & _arg)
  {
    this->heading_error = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    car_msgs::msg::DebugController_<ContainerAllocator> *;
  using ConstRawPtr =
    const car_msgs::msg::DebugController_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<car_msgs::msg::DebugController_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<car_msgs::msg::DebugController_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      car_msgs::msg::DebugController_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<car_msgs::msg::DebugController_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      car_msgs::msg::DebugController_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<car_msgs::msg::DebugController_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<car_msgs::msg::DebugController_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<car_msgs::msg::DebugController_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__car_msgs__msg__DebugController
    std::shared_ptr<car_msgs::msg::DebugController_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__car_msgs__msg__DebugController
    std::shared_ptr<car_msgs::msg::DebugController_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DebugController_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->yaw_rate != other.yaw_rate) {
      return false;
    }
    if (this->yaw != other.yaw) {
      return false;
    }
    if (this->cn_yaw != other.cn_yaw) {
      return false;
    }
    if (this->speed != other.speed) {
      return false;
    }
    if (this->steering_angle != other.steering_angle) {
      return false;
    }
    if (this->pdx_cnode != other.pdx_cnode) {
      return false;
    }
    if (this->cte != other.cte) {
      return false;
    }
    if (this->heading_error != other.heading_error) {
      return false;
    }
    return true;
  }
  bool operator!=(const DebugController_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DebugController_

// alias to use template instance with default allocator
using DebugController =
  car_msgs::msg::DebugController_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace car_msgs

#endif  // CAR_MSGS__MSG__DETAIL__DEBUG_CONTROLLER__STRUCT_HPP_
