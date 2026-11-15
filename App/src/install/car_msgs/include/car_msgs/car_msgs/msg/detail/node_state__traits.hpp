// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from car_msgs:msg/NodeState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/node_state.hpp"


#ifndef CAR_MSGS__MSG__DETAIL__NODE_STATE__TRAITS_HPP_
#define CAR_MSGS__MSG__DETAIL__NODE_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "car_msgs/msg/detail/node_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace car_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const NodeState & msg,
  std::ostream & out)
{
  out << "{";
  // member: localizer_is_ready
  {
    out << "localizer_is_ready: ";
    rosidl_generator_traits::value_to_yaml(msg.localizer_is_ready, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const NodeState & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: localizer_is_ready
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "localizer_is_ready: ";
    rosidl_generator_traits::value_to_yaml(msg.localizer_is_ready, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const NodeState & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace car_msgs

namespace rosidl_generator_traits
{

[[deprecated("use car_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const car_msgs::msg::NodeState & msg,
  std::ostream & out, size_t indentation = 0)
{
  car_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use car_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const car_msgs::msg::NodeState & msg)
{
  return car_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<car_msgs::msg::NodeState>()
{
  return "car_msgs::msg::NodeState";
}

template<>
inline const char * name<car_msgs::msg::NodeState>()
{
  return "car_msgs/msg/NodeState";
}

template<>
struct has_fixed_size<car_msgs::msg::NodeState>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<car_msgs::msg::NodeState>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<car_msgs::msg::NodeState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CAR_MSGS__MSG__DETAIL__NODE_STATE__TRAITS_HPP_
