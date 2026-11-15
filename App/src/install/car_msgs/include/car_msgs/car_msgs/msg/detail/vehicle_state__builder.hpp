// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from car_msgs:msg/VehicleState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/vehicle_state.hpp"


#ifndef CAR_MSGS__MSG__DETAIL__VEHICLE_STATE__BUILDER_HPP_
#define CAR_MSGS__MSG__DETAIL__VEHICLE_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "car_msgs/msg/detail/vehicle_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace car_msgs
{

namespace msg
{

namespace builder
{

class Init_VehicleState_yaw
{
public:
  explicit Init_VehicleState_yaw(::car_msgs::msg::VehicleState & msg)
  : msg_(msg)
  {}
  ::car_msgs::msg::VehicleState yaw(::car_msgs::msg::VehicleState::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return std::move(msg_);
  }

private:
  ::car_msgs::msg::VehicleState msg_;
};

class Init_VehicleState_speed
{
public:
  explicit Init_VehicleState_speed(::car_msgs::msg::VehicleState & msg)
  : msg_(msg)
  {}
  Init_VehicleState_yaw speed(::car_msgs::msg::VehicleState::_speed_type arg)
  {
    msg_.speed = std::move(arg);
    return Init_VehicleState_yaw(msg_);
  }

private:
  ::car_msgs::msg::VehicleState msg_;
};

class Init_VehicleState_pos_y
{
public:
  explicit Init_VehicleState_pos_y(::car_msgs::msg::VehicleState & msg)
  : msg_(msg)
  {}
  Init_VehicleState_speed pos_y(::car_msgs::msg::VehicleState::_pos_y_type arg)
  {
    msg_.pos_y = std::move(arg);
    return Init_VehicleState_speed(msg_);
  }

private:
  ::car_msgs::msg::VehicleState msg_;
};

class Init_VehicleState_pos_x
{
public:
  explicit Init_VehicleState_pos_x(::car_msgs::msg::VehicleState & msg)
  : msg_(msg)
  {}
  Init_VehicleState_pos_y pos_x(::car_msgs::msg::VehicleState::_pos_x_type arg)
  {
    msg_.pos_x = std::move(arg);
    return Init_VehicleState_pos_y(msg_);
  }

private:
  ::car_msgs::msg::VehicleState msg_;
};

class Init_VehicleState_header
{
public:
  Init_VehicleState_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VehicleState_pos_x header(::car_msgs::msg::VehicleState::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_VehicleState_pos_x(msg_);
  }

private:
  ::car_msgs::msg::VehicleState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::car_msgs::msg::VehicleState>()
{
  return car_msgs::msg::builder::Init_VehicleState_header();
}

}  // namespace car_msgs

#endif  // CAR_MSGS__MSG__DETAIL__VEHICLE_STATE__BUILDER_HPP_
