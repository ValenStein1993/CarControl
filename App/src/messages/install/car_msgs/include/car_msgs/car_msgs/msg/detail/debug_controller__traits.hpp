// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from car_msgs:msg/DebugController.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/debug_controller.hpp"


#ifndef CAR_MSGS__MSG__DETAIL__DEBUG_CONTROLLER__TRAITS_HPP_
#define CAR_MSGS__MSG__DETAIL__DEBUG_CONTROLLER__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "car_msgs/msg/detail/debug_controller__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace car_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const DebugController & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: yaw_rate
  {
    out << "yaw_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw_rate, out);
    out << ", ";
  }

  // member: yaw
  {
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << ", ";
  }

  // member: cn_yaw
  {
    out << "cn_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.cn_yaw, out);
    out << ", ";
  }

  // member: speed
  {
    out << "speed: ";
    rosidl_generator_traits::value_to_yaml(msg.speed, out);
    out << ", ";
  }

  // member: steering_angle
  {
    out << "steering_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.steering_angle, out);
    out << ", ";
  }

  // member: idx_closest_node
  {
    out << "idx_closest_node: ";
    rosidl_generator_traits::value_to_yaml(msg.idx_closest_node, out);
    out << ", ";
  }

  // member: cte
  {
    out << "cte: ";
    rosidl_generator_traits::value_to_yaml(msg.cte, out);
    out << ", ";
  }

  // member: heading_error
  {
    out << "heading_error: ";
    rosidl_generator_traits::value_to_yaml(msg.heading_error, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DebugController & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: yaw_rate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw_rate, out);
    out << "\n";
  }

  // member: yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << "\n";
  }

  // member: cn_yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cn_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.cn_yaw, out);
    out << "\n";
  }

  // member: speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "speed: ";
    rosidl_generator_traits::value_to_yaml(msg.speed, out);
    out << "\n";
  }

  // member: steering_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "steering_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.steering_angle, out);
    out << "\n";
  }

  // member: idx_closest_node
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "idx_closest_node: ";
    rosidl_generator_traits::value_to_yaml(msg.idx_closest_node, out);
    out << "\n";
  }

  // member: cte
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cte: ";
    rosidl_generator_traits::value_to_yaml(msg.cte, out);
    out << "\n";
  }

  // member: heading_error
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "heading_error: ";
    rosidl_generator_traits::value_to_yaml(msg.heading_error, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DebugController & msg, bool use_flow_style = false)
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
  const car_msgs::msg::DebugController & msg,
  std::ostream & out, size_t indentation = 0)
{
  car_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use car_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const car_msgs::msg::DebugController & msg)
{
  return car_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<car_msgs::msg::DebugController>()
{
  return "car_msgs::msg::DebugController";
}

template<>
inline const char * name<car_msgs::msg::DebugController>()
{
  return "car_msgs/msg/DebugController";
}

template<>
struct has_fixed_size<car_msgs::msg::DebugController>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<car_msgs::msg::DebugController>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<car_msgs::msg::DebugController>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CAR_MSGS__MSG__DETAIL__DEBUG_CONTROLLER__TRAITS_HPP_
