// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from car_msgs:msg/PathNode.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/path_node.hpp"


#ifndef CAR_MSGS__MSG__DETAIL__PATH_NODE__TRAITS_HPP_
#define CAR_MSGS__MSG__DETAIL__PATH_NODE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "car_msgs/msg/detail/path_node__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace car_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const PathNode & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: th
  {
    out << "th: ";
    rosidl_generator_traits::value_to_yaml(msg.th, out);
    out << ", ";
  }

  // member: idx
  {
    out << "idx: ";
    rosidl_generator_traits::value_to_yaml(msg.idx, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PathNode & msg,
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

  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: th
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "th: ";
    rosidl_generator_traits::value_to_yaml(msg.th, out);
    out << "\n";
  }

  // member: idx
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "idx: ";
    rosidl_generator_traits::value_to_yaml(msg.idx, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PathNode & msg, bool use_flow_style = false)
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
  const car_msgs::msg::PathNode & msg,
  std::ostream & out, size_t indentation = 0)
{
  car_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use car_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const car_msgs::msg::PathNode & msg)
{
  return car_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<car_msgs::msg::PathNode>()
{
  return "car_msgs::msg::PathNode";
}

template<>
inline const char * name<car_msgs::msg::PathNode>()
{
  return "car_msgs/msg/PathNode";
}

template<>
struct has_fixed_size<car_msgs::msg::PathNode>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<car_msgs::msg::PathNode>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<car_msgs::msg::PathNode>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CAR_MSGS__MSG__DETAIL__PATH_NODE__TRAITS_HPP_
