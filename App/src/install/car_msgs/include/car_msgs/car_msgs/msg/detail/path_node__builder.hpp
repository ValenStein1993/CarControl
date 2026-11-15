// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from car_msgs:msg/PathNode.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/path_node.hpp"


#ifndef CAR_MSGS__MSG__DETAIL__PATH_NODE__BUILDER_HPP_
#define CAR_MSGS__MSG__DETAIL__PATH_NODE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "car_msgs/msg/detail/path_node__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace car_msgs
{

namespace msg
{

namespace builder
{

class Init_PathNode_idx
{
public:
  explicit Init_PathNode_idx(::car_msgs::msg::PathNode & msg)
  : msg_(msg)
  {}
  ::car_msgs::msg::PathNode idx(::car_msgs::msg::PathNode::_idx_type arg)
  {
    msg_.idx = std::move(arg);
    return std::move(msg_);
  }

private:
  ::car_msgs::msg::PathNode msg_;
};

class Init_PathNode_th
{
public:
  explicit Init_PathNode_th(::car_msgs::msg::PathNode & msg)
  : msg_(msg)
  {}
  Init_PathNode_idx th(::car_msgs::msg::PathNode::_th_type arg)
  {
    msg_.th = std::move(arg);
    return Init_PathNode_idx(msg_);
  }

private:
  ::car_msgs::msg::PathNode msg_;
};

class Init_PathNode_y
{
public:
  explicit Init_PathNode_y(::car_msgs::msg::PathNode & msg)
  : msg_(msg)
  {}
  Init_PathNode_th y(::car_msgs::msg::PathNode::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_PathNode_th(msg_);
  }

private:
  ::car_msgs::msg::PathNode msg_;
};

class Init_PathNode_x
{
public:
  explicit Init_PathNode_x(::car_msgs::msg::PathNode & msg)
  : msg_(msg)
  {}
  Init_PathNode_y x(::car_msgs::msg::PathNode::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_PathNode_y(msg_);
  }

private:
  ::car_msgs::msg::PathNode msg_;
};

class Init_PathNode_header
{
public:
  Init_PathNode_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PathNode_x header(::car_msgs::msg::PathNode::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_PathNode_x(msg_);
  }

private:
  ::car_msgs::msg::PathNode msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::car_msgs::msg::PathNode>()
{
  return car_msgs::msg::builder::Init_PathNode_header();
}

}  // namespace car_msgs

#endif  // CAR_MSGS__MSG__DETAIL__PATH_NODE__BUILDER_HPP_
