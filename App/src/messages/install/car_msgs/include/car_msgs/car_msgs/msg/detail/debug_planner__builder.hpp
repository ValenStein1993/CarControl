// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from car_msgs:msg/DebugPlanner.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/debug_planner.hpp"


#ifndef CAR_MSGS__MSG__DETAIL__DEBUG_PLANNER__BUILDER_HPP_
#define CAR_MSGS__MSG__DETAIL__DEBUG_PLANNER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "car_msgs/msg/detail/debug_planner__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace car_msgs
{

namespace msg
{

namespace builder
{

class Init_DebugPlanner_idx_update_node
{
public:
  explicit Init_DebugPlanner_idx_update_node(::car_msgs::msg::DebugPlanner & msg)
  : msg_(msg)
  {}
  ::car_msgs::msg::DebugPlanner idx_update_node(::car_msgs::msg::DebugPlanner::_idx_update_node_type arg)
  {
    msg_.idx_update_node = std::move(arg);
    return std::move(msg_);
  }

private:
  ::car_msgs::msg::DebugPlanner msg_;
};

class Init_DebugPlanner_length_path
{
public:
  explicit Init_DebugPlanner_length_path(::car_msgs::msg::DebugPlanner & msg)
  : msg_(msg)
  {}
  Init_DebugPlanner_idx_update_node length_path(::car_msgs::msg::DebugPlanner::_length_path_type arg)
  {
    msg_.length_path = std::move(arg);
    return Init_DebugPlanner_idx_update_node(msg_);
  }

private:
  ::car_msgs::msg::DebugPlanner msg_;
};

class Init_DebugPlanner_header
{
public:
  Init_DebugPlanner_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DebugPlanner_length_path header(::car_msgs::msg::DebugPlanner::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_DebugPlanner_length_path(msg_);
  }

private:
  ::car_msgs::msg::DebugPlanner msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::car_msgs::msg::DebugPlanner>()
{
  return car_msgs::msg::builder::Init_DebugPlanner_header();
}

}  // namespace car_msgs

#endif  // CAR_MSGS__MSG__DETAIL__DEBUG_PLANNER__BUILDER_HPP_
