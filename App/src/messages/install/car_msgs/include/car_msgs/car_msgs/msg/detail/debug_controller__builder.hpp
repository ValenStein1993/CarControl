// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from car_msgs:msg/DebugController.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/debug_controller.hpp"


#ifndef CAR_MSGS__MSG__DETAIL__DEBUG_CONTROLLER__BUILDER_HPP_
#define CAR_MSGS__MSG__DETAIL__DEBUG_CONTROLLER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "car_msgs/msg/detail/debug_controller__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace car_msgs
{

namespace msg
{

namespace builder
{

class Init_DebugController_heading_error
{
public:
  explicit Init_DebugController_heading_error(::car_msgs::msg::DebugController & msg)
  : msg_(msg)
  {}
  ::car_msgs::msg::DebugController heading_error(::car_msgs::msg::DebugController::_heading_error_type arg)
  {
    msg_.heading_error = std::move(arg);
    return std::move(msg_);
  }

private:
  ::car_msgs::msg::DebugController msg_;
};

class Init_DebugController_cte
{
public:
  explicit Init_DebugController_cte(::car_msgs::msg::DebugController & msg)
  : msg_(msg)
  {}
  Init_DebugController_heading_error cte(::car_msgs::msg::DebugController::_cte_type arg)
  {
    msg_.cte = std::move(arg);
    return Init_DebugController_heading_error(msg_);
  }

private:
  ::car_msgs::msg::DebugController msg_;
};

class Init_DebugController_idx_closest_node
{
public:
  explicit Init_DebugController_idx_closest_node(::car_msgs::msg::DebugController & msg)
  : msg_(msg)
  {}
  Init_DebugController_cte idx_closest_node(::car_msgs::msg::DebugController::_idx_closest_node_type arg)
  {
    msg_.idx_closest_node = std::move(arg);
    return Init_DebugController_cte(msg_);
  }

private:
  ::car_msgs::msg::DebugController msg_;
};

class Init_DebugController_steering_angle
{
public:
  explicit Init_DebugController_steering_angle(::car_msgs::msg::DebugController & msg)
  : msg_(msg)
  {}
  Init_DebugController_idx_closest_node steering_angle(::car_msgs::msg::DebugController::_steering_angle_type arg)
  {
    msg_.steering_angle = std::move(arg);
    return Init_DebugController_idx_closest_node(msg_);
  }

private:
  ::car_msgs::msg::DebugController msg_;
};

class Init_DebugController_speed
{
public:
  explicit Init_DebugController_speed(::car_msgs::msg::DebugController & msg)
  : msg_(msg)
  {}
  Init_DebugController_steering_angle speed(::car_msgs::msg::DebugController::_speed_type arg)
  {
    msg_.speed = std::move(arg);
    return Init_DebugController_steering_angle(msg_);
  }

private:
  ::car_msgs::msg::DebugController msg_;
};

class Init_DebugController_cn_yaw
{
public:
  explicit Init_DebugController_cn_yaw(::car_msgs::msg::DebugController & msg)
  : msg_(msg)
  {}
  Init_DebugController_speed cn_yaw(::car_msgs::msg::DebugController::_cn_yaw_type arg)
  {
    msg_.cn_yaw = std::move(arg);
    return Init_DebugController_speed(msg_);
  }

private:
  ::car_msgs::msg::DebugController msg_;
};

class Init_DebugController_yaw
{
public:
  explicit Init_DebugController_yaw(::car_msgs::msg::DebugController & msg)
  : msg_(msg)
  {}
  Init_DebugController_cn_yaw yaw(::car_msgs::msg::DebugController::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return Init_DebugController_cn_yaw(msg_);
  }

private:
  ::car_msgs::msg::DebugController msg_;
};

class Init_DebugController_yaw_rate
{
public:
  explicit Init_DebugController_yaw_rate(::car_msgs::msg::DebugController & msg)
  : msg_(msg)
  {}
  Init_DebugController_yaw yaw_rate(::car_msgs::msg::DebugController::_yaw_rate_type arg)
  {
    msg_.yaw_rate = std::move(arg);
    return Init_DebugController_yaw(msg_);
  }

private:
  ::car_msgs::msg::DebugController msg_;
};

class Init_DebugController_header
{
public:
  Init_DebugController_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DebugController_yaw_rate header(::car_msgs::msg::DebugController::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_DebugController_yaw_rate(msg_);
  }

private:
  ::car_msgs::msg::DebugController msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::car_msgs::msg::DebugController>()
{
  return car_msgs::msg::builder::Init_DebugController_header();
}

}  // namespace car_msgs

#endif  // CAR_MSGS__MSG__DETAIL__DEBUG_CONTROLLER__BUILDER_HPP_
