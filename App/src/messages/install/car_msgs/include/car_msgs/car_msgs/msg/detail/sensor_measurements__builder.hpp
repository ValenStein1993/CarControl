// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from car_msgs:msg/SensorMeasurements.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/sensor_measurements.hpp"


#ifndef CAR_MSGS__MSG__DETAIL__SENSOR_MEASUREMENTS__BUILDER_HPP_
#define CAR_MSGS__MSG__DETAIL__SENSOR_MEASUREMENTS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "car_msgs/msg/detail/sensor_measurements__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace car_msgs
{

namespace msg
{

namespace builder
{

class Init_SensorMeasurements_wheelencoder_translspeed
{
public:
  explicit Init_SensorMeasurements_wheelencoder_translspeed(::car_msgs::msg::SensorMeasurements & msg)
  : msg_(msg)
  {}
  ::car_msgs::msg::SensorMeasurements wheelencoder_translspeed(::car_msgs::msg::SensorMeasurements::_wheelencoder_translspeed_type arg)
  {
    msg_.wheelencoder_translspeed = std::move(arg);
    return std::move(msg_);
  }

private:
  ::car_msgs::msg::SensorMeasurements msg_;
};

class Init_SensorMeasurements_wheelencoder_rotspeed
{
public:
  explicit Init_SensorMeasurements_wheelencoder_rotspeed(::car_msgs::msg::SensorMeasurements & msg)
  : msg_(msg)
  {}
  Init_SensorMeasurements_wheelencoder_translspeed wheelencoder_rotspeed(::car_msgs::msg::SensorMeasurements::_wheelencoder_rotspeed_type arg)
  {
    msg_.wheelencoder_rotspeed = std::move(arg);
    return Init_SensorMeasurements_wheelencoder_translspeed(msg_);
  }

private:
  ::car_msgs::msg::SensorMeasurements msg_;
};

class Init_SensorMeasurements_cjmcu103_anglespeed
{
public:
  explicit Init_SensorMeasurements_cjmcu103_anglespeed(::car_msgs::msg::SensorMeasurements & msg)
  : msg_(msg)
  {}
  Init_SensorMeasurements_wheelencoder_rotspeed cjmcu103_anglespeed(::car_msgs::msg::SensorMeasurements::_cjmcu103_anglespeed_type arg)
  {
    msg_.cjmcu103_anglespeed = std::move(arg);
    return Init_SensorMeasurements_wheelencoder_rotspeed(msg_);
  }

private:
  ::car_msgs::msg::SensorMeasurements msg_;
};

class Init_SensorMeasurements_cjmcu103_angle
{
public:
  explicit Init_SensorMeasurements_cjmcu103_angle(::car_msgs::msg::SensorMeasurements & msg)
  : msg_(msg)
  {}
  Init_SensorMeasurements_cjmcu103_anglespeed cjmcu103_angle(::car_msgs::msg::SensorMeasurements::_cjmcu103_angle_type arg)
  {
    msg_.cjmcu103_angle = std::move(arg);
    return Init_SensorMeasurements_cjmcu103_anglespeed(msg_);
  }

private:
  ::car_msgs::msg::SensorMeasurements msg_;
};

class Init_SensorMeasurements_ina219_power
{
public:
  explicit Init_SensorMeasurements_ina219_power(::car_msgs::msg::SensorMeasurements & msg)
  : msg_(msg)
  {}
  Init_SensorMeasurements_cjmcu103_angle ina219_power(::car_msgs::msg::SensorMeasurements::_ina219_power_type arg)
  {
    msg_.ina219_power = std::move(arg);
    return Init_SensorMeasurements_cjmcu103_angle(msg_);
  }

private:
  ::car_msgs::msg::SensorMeasurements msg_;
};

class Init_SensorMeasurements_ina219_current
{
public:
  explicit Init_SensorMeasurements_ina219_current(::car_msgs::msg::SensorMeasurements & msg)
  : msg_(msg)
  {}
  Init_SensorMeasurements_ina219_power ina219_current(::car_msgs::msg::SensorMeasurements::_ina219_current_type arg)
  {
    msg_.ina219_current = std::move(arg);
    return Init_SensorMeasurements_ina219_power(msg_);
  }

private:
  ::car_msgs::msg::SensorMeasurements msg_;
};

class Init_SensorMeasurements_mpu6050_gyro_z
{
public:
  explicit Init_SensorMeasurements_mpu6050_gyro_z(::car_msgs::msg::SensorMeasurements & msg)
  : msg_(msg)
  {}
  Init_SensorMeasurements_ina219_current mpu6050_gyro_z(::car_msgs::msg::SensorMeasurements::_mpu6050_gyro_z_type arg)
  {
    msg_.mpu6050_gyro_z = std::move(arg);
    return Init_SensorMeasurements_ina219_current(msg_);
  }

private:
  ::car_msgs::msg::SensorMeasurements msg_;
};

class Init_SensorMeasurements_mpu6050_gyro_y
{
public:
  explicit Init_SensorMeasurements_mpu6050_gyro_y(::car_msgs::msg::SensorMeasurements & msg)
  : msg_(msg)
  {}
  Init_SensorMeasurements_mpu6050_gyro_z mpu6050_gyro_y(::car_msgs::msg::SensorMeasurements::_mpu6050_gyro_y_type arg)
  {
    msg_.mpu6050_gyro_y = std::move(arg);
    return Init_SensorMeasurements_mpu6050_gyro_z(msg_);
  }

private:
  ::car_msgs::msg::SensorMeasurements msg_;
};

class Init_SensorMeasurements_mpu6050_gyro_x
{
public:
  explicit Init_SensorMeasurements_mpu6050_gyro_x(::car_msgs::msg::SensorMeasurements & msg)
  : msg_(msg)
  {}
  Init_SensorMeasurements_mpu6050_gyro_y mpu6050_gyro_x(::car_msgs::msg::SensorMeasurements::_mpu6050_gyro_x_type arg)
  {
    msg_.mpu6050_gyro_x = std::move(arg);
    return Init_SensorMeasurements_mpu6050_gyro_y(msg_);
  }

private:
  ::car_msgs::msg::SensorMeasurements msg_;
};

class Init_SensorMeasurements_mpu6050_accel_z
{
public:
  explicit Init_SensorMeasurements_mpu6050_accel_z(::car_msgs::msg::SensorMeasurements & msg)
  : msg_(msg)
  {}
  Init_SensorMeasurements_mpu6050_gyro_x mpu6050_accel_z(::car_msgs::msg::SensorMeasurements::_mpu6050_accel_z_type arg)
  {
    msg_.mpu6050_accel_z = std::move(arg);
    return Init_SensorMeasurements_mpu6050_gyro_x(msg_);
  }

private:
  ::car_msgs::msg::SensorMeasurements msg_;
};

class Init_SensorMeasurements_mpu6050_accel_y
{
public:
  explicit Init_SensorMeasurements_mpu6050_accel_y(::car_msgs::msg::SensorMeasurements & msg)
  : msg_(msg)
  {}
  Init_SensorMeasurements_mpu6050_accel_z mpu6050_accel_y(::car_msgs::msg::SensorMeasurements::_mpu6050_accel_y_type arg)
  {
    msg_.mpu6050_accel_y = std::move(arg);
    return Init_SensorMeasurements_mpu6050_accel_z(msg_);
  }

private:
  ::car_msgs::msg::SensorMeasurements msg_;
};

class Init_SensorMeasurements_mpu6050_accel_x
{
public:
  explicit Init_SensorMeasurements_mpu6050_accel_x(::car_msgs::msg::SensorMeasurements & msg)
  : msg_(msg)
  {}
  Init_SensorMeasurements_mpu6050_accel_y mpu6050_accel_x(::car_msgs::msg::SensorMeasurements::_mpu6050_accel_x_type arg)
  {
    msg_.mpu6050_accel_x = std::move(arg);
    return Init_SensorMeasurements_mpu6050_accel_y(msg_);
  }

private:
  ::car_msgs::msg::SensorMeasurements msg_;
};

class Init_SensorMeasurements_header
{
public:
  Init_SensorMeasurements_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SensorMeasurements_mpu6050_accel_x header(::car_msgs::msg::SensorMeasurements::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_SensorMeasurements_mpu6050_accel_x(msg_);
  }

private:
  ::car_msgs::msg::SensorMeasurements msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::car_msgs::msg::SensorMeasurements>()
{
  return car_msgs::msg::builder::Init_SensorMeasurements_header();
}

}  // namespace car_msgs

#endif  // CAR_MSGS__MSG__DETAIL__SENSOR_MEASUREMENTS__BUILDER_HPP_
