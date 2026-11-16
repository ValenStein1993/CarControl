// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from car_msgs:msg/VehicleState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/vehicle_state.hpp"


#ifndef CAR_MSGS__MSG__DETAIL__VEHICLE_STATE__STRUCT_HPP_
#define CAR_MSGS__MSG__DETAIL__VEHICLE_STATE__STRUCT_HPP_

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
# define DEPRECATED__car_msgs__msg__VehicleState __attribute__((deprecated))
#else
# define DEPRECATED__car_msgs__msg__VehicleState __declspec(deprecated)
#endif

namespace car_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct VehicleState_
{
  using Type = VehicleState_<ContainerAllocator>;

  explicit VehicleState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pos_x = 0.0f;
      this->pos_y = 0.0f;
      this->speed = 0.0f;
      this->yaw = 0.0f;
    }
  }

  explicit VehicleState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pos_x = 0.0f;
      this->pos_y = 0.0f;
      this->speed = 0.0f;
      this->yaw = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _pos_x_type =
    float;
  _pos_x_type pos_x;
  using _pos_y_type =
    float;
  _pos_y_type pos_y;
  using _speed_type =
    float;
  _speed_type speed;
  using _yaw_type =
    float;
  _yaw_type yaw;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__pos_x(
    const float & _arg)
  {
    this->pos_x = _arg;
    return *this;
  }
  Type & set__pos_y(
    const float & _arg)
  {
    this->pos_y = _arg;
    return *this;
  }
  Type & set__speed(
    const float & _arg)
  {
    this->speed = _arg;
    return *this;
  }
  Type & set__yaw(
    const float & _arg)
  {
    this->yaw = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    car_msgs::msg::VehicleState_<ContainerAllocator> *;
  using ConstRawPtr =
    const car_msgs::msg::VehicleState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<car_msgs::msg::VehicleState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<car_msgs::msg::VehicleState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      car_msgs::msg::VehicleState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<car_msgs::msg::VehicleState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      car_msgs::msg::VehicleState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<car_msgs::msg::VehicleState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<car_msgs::msg::VehicleState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<car_msgs::msg::VehicleState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__car_msgs__msg__VehicleState
    std::shared_ptr<car_msgs::msg::VehicleState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__car_msgs__msg__VehicleState
    std::shared_ptr<car_msgs::msg::VehicleState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VehicleState_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->pos_x != other.pos_x) {
      return false;
    }
    if (this->pos_y != other.pos_y) {
      return false;
    }
    if (this->speed != other.speed) {
      return false;
    }
    if (this->yaw != other.yaw) {
      return false;
    }
    return true;
  }
  bool operator!=(const VehicleState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VehicleState_

// alias to use template instance with default allocator
using VehicleState =
  car_msgs::msg::VehicleState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace car_msgs

#endif  // CAR_MSGS__MSG__DETAIL__VEHICLE_STATE__STRUCT_HPP_
