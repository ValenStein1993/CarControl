// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from car_msgs:msg/SensorMeasurements.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/sensor_measurements.hpp"


#ifndef CAR_MSGS__MSG__DETAIL__SENSOR_MEASUREMENTS__TRAITS_HPP_
#define CAR_MSGS__MSG__DETAIL__SENSOR_MEASUREMENTS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "car_msgs/msg/detail/sensor_measurements__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace car_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const SensorMeasurements & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: mpu6050_accel_x
  {
    out << "mpu6050_accel_x: ";
    rosidl_generator_traits::value_to_yaml(msg.mpu6050_accel_x, out);
    out << ", ";
  }

  // member: mpu6050_accel_y
  {
    out << "mpu6050_accel_y: ";
    rosidl_generator_traits::value_to_yaml(msg.mpu6050_accel_y, out);
    out << ", ";
  }

  // member: mpu6050_accel_z
  {
    out << "mpu6050_accel_z: ";
    rosidl_generator_traits::value_to_yaml(msg.mpu6050_accel_z, out);
    out << ", ";
  }

  // member: mpu6050_gyro_x
  {
    out << "mpu6050_gyro_x: ";
    rosidl_generator_traits::value_to_yaml(msg.mpu6050_gyro_x, out);
    out << ", ";
  }

  // member: mpu6050_gyro_y
  {
    out << "mpu6050_gyro_y: ";
    rosidl_generator_traits::value_to_yaml(msg.mpu6050_gyro_y, out);
    out << ", ";
  }

  // member: mpu6050_gyro_z
  {
    out << "mpu6050_gyro_z: ";
    rosidl_generator_traits::value_to_yaml(msg.mpu6050_gyro_z, out);
    out << ", ";
  }

  // member: ina219_current
  {
    out << "ina219_current: ";
    rosidl_generator_traits::value_to_yaml(msg.ina219_current, out);
    out << ", ";
  }

  // member: ina219_power
  {
    out << "ina219_power: ";
    rosidl_generator_traits::value_to_yaml(msg.ina219_power, out);
    out << ", ";
  }

  // member: cjmcu103_angle
  {
    out << "cjmcu103_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.cjmcu103_angle, out);
    out << ", ";
  }

  // member: cjmcu103_anglespeed
  {
    out << "cjmcu103_anglespeed: ";
    rosidl_generator_traits::value_to_yaml(msg.cjmcu103_anglespeed, out);
    out << ", ";
  }

  // member: wheelencoder_rotspeed
  {
    out << "wheelencoder_rotspeed: ";
    rosidl_generator_traits::value_to_yaml(msg.wheelencoder_rotspeed, out);
    out << ", ";
  }

  // member: wheelencoder_translspeed
  {
    out << "wheelencoder_translspeed: ";
    rosidl_generator_traits::value_to_yaml(msg.wheelencoder_translspeed, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SensorMeasurements & msg,
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

  // member: mpu6050_accel_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mpu6050_accel_x: ";
    rosidl_generator_traits::value_to_yaml(msg.mpu6050_accel_x, out);
    out << "\n";
  }

  // member: mpu6050_accel_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mpu6050_accel_y: ";
    rosidl_generator_traits::value_to_yaml(msg.mpu6050_accel_y, out);
    out << "\n";
  }

  // member: mpu6050_accel_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mpu6050_accel_z: ";
    rosidl_generator_traits::value_to_yaml(msg.mpu6050_accel_z, out);
    out << "\n";
  }

  // member: mpu6050_gyro_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mpu6050_gyro_x: ";
    rosidl_generator_traits::value_to_yaml(msg.mpu6050_gyro_x, out);
    out << "\n";
  }

  // member: mpu6050_gyro_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mpu6050_gyro_y: ";
    rosidl_generator_traits::value_to_yaml(msg.mpu6050_gyro_y, out);
    out << "\n";
  }

  // member: mpu6050_gyro_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mpu6050_gyro_z: ";
    rosidl_generator_traits::value_to_yaml(msg.mpu6050_gyro_z, out);
    out << "\n";
  }

  // member: ina219_current
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ina219_current: ";
    rosidl_generator_traits::value_to_yaml(msg.ina219_current, out);
    out << "\n";
  }

  // member: ina219_power
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ina219_power: ";
    rosidl_generator_traits::value_to_yaml(msg.ina219_power, out);
    out << "\n";
  }

  // member: cjmcu103_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cjmcu103_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.cjmcu103_angle, out);
    out << "\n";
  }

  // member: cjmcu103_anglespeed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cjmcu103_anglespeed: ";
    rosidl_generator_traits::value_to_yaml(msg.cjmcu103_anglespeed, out);
    out << "\n";
  }

  // member: wheelencoder_rotspeed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "wheelencoder_rotspeed: ";
    rosidl_generator_traits::value_to_yaml(msg.wheelencoder_rotspeed, out);
    out << "\n";
  }

  // member: wheelencoder_translspeed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "wheelencoder_translspeed: ";
    rosidl_generator_traits::value_to_yaml(msg.wheelencoder_translspeed, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SensorMeasurements & msg, bool use_flow_style = false)
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
  const car_msgs::msg::SensorMeasurements & msg,
  std::ostream & out, size_t indentation = 0)
{
  car_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use car_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const car_msgs::msg::SensorMeasurements & msg)
{
  return car_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<car_msgs::msg::SensorMeasurements>()
{
  return "car_msgs::msg::SensorMeasurements";
}

template<>
inline const char * name<car_msgs::msg::SensorMeasurements>()
{
  return "car_msgs/msg/SensorMeasurements";
}

template<>
struct has_fixed_size<car_msgs::msg::SensorMeasurements>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<car_msgs::msg::SensorMeasurements>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<car_msgs::msg::SensorMeasurements>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CAR_MSGS__MSG__DETAIL__SENSOR_MEASUREMENTS__TRAITS_HPP_
