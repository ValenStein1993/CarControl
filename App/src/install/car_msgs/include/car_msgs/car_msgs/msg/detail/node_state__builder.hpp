// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from car_msgs:msg/NodeState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/node_state.hpp"


#ifndef CAR_MSGS__MSG__DETAIL__NODE_STATE__BUILDER_HPP_
#define CAR_MSGS__MSG__DETAIL__NODE_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "car_msgs/msg/detail/node_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace car_msgs
{

namespace msg
{

namespace builder
{

class Init_NodeState_localizer_is_ready
{
public:
  Init_NodeState_localizer_is_ready()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::car_msgs::msg::NodeState localizer_is_ready(::car_msgs::msg::NodeState::_localizer_is_ready_type arg)
  {
    msg_.localizer_is_ready = std::move(arg);
    return std::move(msg_);
  }

private:
  ::car_msgs::msg::NodeState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::car_msgs::msg::NodeState>()
{
  return car_msgs::msg::builder::Init_NodeState_localizer_is_ready();
}

}  // namespace car_msgs

#endif  // CAR_MSGS__MSG__DETAIL__NODE_STATE__BUILDER_HPP_
