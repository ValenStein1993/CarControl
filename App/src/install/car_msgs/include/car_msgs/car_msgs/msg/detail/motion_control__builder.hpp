// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from car_msgs:msg/MotionControl.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/motion_control.hpp"


#ifndef CAR_MSGS__MSG__DETAIL__MOTION_CONTROL__BUILDER_HPP_
#define CAR_MSGS__MSG__DETAIL__MOTION_CONTROL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "car_msgs/msg/detail/motion_control__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace car_msgs
{

namespace msg
{

namespace builder
{

class Init_MotionControl_speed
{
public:
  explicit Init_MotionControl_speed(::car_msgs::msg::MotionControl & msg)
  : msg_(msg)
  {}
  ::car_msgs::msg::MotionControl speed(::car_msgs::msg::MotionControl::_speed_type arg)
  {
    msg_.speed = std::move(arg);
    return std::move(msg_);
  }

private:
  ::car_msgs::msg::MotionControl msg_;
};

class Init_MotionControl_yaw_rate
{
public:
  explicit Init_MotionControl_yaw_rate(::car_msgs::msg::MotionControl & msg)
  : msg_(msg)
  {}
  Init_MotionControl_speed yaw_rate(::car_msgs::msg::MotionControl::_yaw_rate_type arg)
  {
    msg_.yaw_rate = std::move(arg);
    return Init_MotionControl_speed(msg_);
  }

private:
  ::car_msgs::msg::MotionControl msg_;
};

class Init_MotionControl_header
{
public:
  Init_MotionControl_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotionControl_yaw_rate header(::car_msgs::msg::MotionControl::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_MotionControl_yaw_rate(msg_);
  }

private:
  ::car_msgs::msg::MotionControl msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::car_msgs::msg::MotionControl>()
{
  return car_msgs::msg::builder::Init_MotionControl_header();
}

}  // namespace car_msgs

#endif  // CAR_MSGS__MSG__DETAIL__MOTION_CONTROL__BUILDER_HPP_
