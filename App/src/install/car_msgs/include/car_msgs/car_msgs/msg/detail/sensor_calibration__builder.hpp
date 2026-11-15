// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from car_msgs:msg/SensorCalibration.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/sensor_calibration.hpp"


#ifndef CAR_MSGS__MSG__DETAIL__SENSOR_CALIBRATION__BUILDER_HPP_
#define CAR_MSGS__MSG__DETAIL__SENSOR_CALIBRATION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "car_msgs/msg/detail/sensor_calibration__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace car_msgs
{

namespace msg
{

namespace builder
{

class Init_SensorCalibration_wheelencoder_var_rotspeed
{
public:
  explicit Init_SensorCalibration_wheelencoder_var_rotspeed(::car_msgs::msg::SensorCalibration & msg)
  : msg_(msg)
  {}
  ::car_msgs::msg::SensorCalibration wheelencoder_var_rotspeed(::car_msgs::msg::SensorCalibration::_wheelencoder_var_rotspeed_type arg)
  {
    msg_.wheelencoder_var_rotspeed = std::move(arg);
    return std::move(msg_);
  }

private:
  ::car_msgs::msg::SensorCalibration msg_;
};

class Init_SensorCalibration_cjmcu103_var_anglespeed
{
public:
  explicit Init_SensorCalibration_cjmcu103_var_anglespeed(::car_msgs::msg::SensorCalibration & msg)
  : msg_(msg)
  {}
  Init_SensorCalibration_wheelencoder_var_rotspeed cjmcu103_var_anglespeed(::car_msgs::msg::SensorCalibration::_cjmcu103_var_anglespeed_type arg)
  {
    msg_.cjmcu103_var_anglespeed = std::move(arg);
    return Init_SensorCalibration_wheelencoder_var_rotspeed(msg_);
  }

private:
  ::car_msgs::msg::SensorCalibration msg_;
};

class Init_SensorCalibration_cjmcu103_mean_anglespeed
{
public:
  explicit Init_SensorCalibration_cjmcu103_mean_anglespeed(::car_msgs::msg::SensorCalibration & msg)
  : msg_(msg)
  {}
  Init_SensorCalibration_cjmcu103_var_anglespeed cjmcu103_mean_anglespeed(::car_msgs::msg::SensorCalibration::_cjmcu103_mean_anglespeed_type arg)
  {
    msg_.cjmcu103_mean_anglespeed = std::move(arg);
    return Init_SensorCalibration_cjmcu103_var_anglespeed(msg_);
  }

private:
  ::car_msgs::msg::SensorCalibration msg_;
};

class Init_SensorCalibration_cjmcu103_var_angle
{
public:
  explicit Init_SensorCalibration_cjmcu103_var_angle(::car_msgs::msg::SensorCalibration & msg)
  : msg_(msg)
  {}
  Init_SensorCalibration_cjmcu103_mean_anglespeed cjmcu103_var_angle(::car_msgs::msg::SensorCalibration::_cjmcu103_var_angle_type arg)
  {
    msg_.cjmcu103_var_angle = std::move(arg);
    return Init_SensorCalibration_cjmcu103_mean_anglespeed(msg_);
  }

private:
  ::car_msgs::msg::SensorCalibration msg_;
};

class Init_SensorCalibration_cjmcu103_mean_angle
{
public:
  explicit Init_SensorCalibration_cjmcu103_mean_angle(::car_msgs::msg::SensorCalibration & msg)
  : msg_(msg)
  {}
  Init_SensorCalibration_cjmcu103_var_angle cjmcu103_mean_angle(::car_msgs::msg::SensorCalibration::_cjmcu103_mean_angle_type arg)
  {
    msg_.cjmcu103_mean_angle = std::move(arg);
    return Init_SensorCalibration_cjmcu103_var_angle(msg_);
  }

private:
  ::car_msgs::msg::SensorCalibration msg_;
};

class Init_SensorCalibration_mpu6050_var_gyro_z
{
public:
  explicit Init_SensorCalibration_mpu6050_var_gyro_z(::car_msgs::msg::SensorCalibration & msg)
  : msg_(msg)
  {}
  Init_SensorCalibration_cjmcu103_mean_angle mpu6050_var_gyro_z(::car_msgs::msg::SensorCalibration::_mpu6050_var_gyro_z_type arg)
  {
    msg_.mpu6050_var_gyro_z = std::move(arg);
    return Init_SensorCalibration_cjmcu103_mean_angle(msg_);
  }

private:
  ::car_msgs::msg::SensorCalibration msg_;
};

class Init_SensorCalibration_mpu6050_var_gyro_y
{
public:
  explicit Init_SensorCalibration_mpu6050_var_gyro_y(::car_msgs::msg::SensorCalibration & msg)
  : msg_(msg)
  {}
  Init_SensorCalibration_mpu6050_var_gyro_z mpu6050_var_gyro_y(::car_msgs::msg::SensorCalibration::_mpu6050_var_gyro_y_type arg)
  {
    msg_.mpu6050_var_gyro_y = std::move(arg);
    return Init_SensorCalibration_mpu6050_var_gyro_z(msg_);
  }

private:
  ::car_msgs::msg::SensorCalibration msg_;
};

class Init_SensorCalibration_mpu6050_var_gyro_x
{
public:
  explicit Init_SensorCalibration_mpu6050_var_gyro_x(::car_msgs::msg::SensorCalibration & msg)
  : msg_(msg)
  {}
  Init_SensorCalibration_mpu6050_var_gyro_y mpu6050_var_gyro_x(::car_msgs::msg::SensorCalibration::_mpu6050_var_gyro_x_type arg)
  {
    msg_.mpu6050_var_gyro_x = std::move(arg);
    return Init_SensorCalibration_mpu6050_var_gyro_y(msg_);
  }

private:
  ::car_msgs::msg::SensorCalibration msg_;
};

class Init_SensorCalibration_mpu6050_mean_gyro_z
{
public:
  explicit Init_SensorCalibration_mpu6050_mean_gyro_z(::car_msgs::msg::SensorCalibration & msg)
  : msg_(msg)
  {}
  Init_SensorCalibration_mpu6050_var_gyro_x mpu6050_mean_gyro_z(::car_msgs::msg::SensorCalibration::_mpu6050_mean_gyro_z_type arg)
  {
    msg_.mpu6050_mean_gyro_z = std::move(arg);
    return Init_SensorCalibration_mpu6050_var_gyro_x(msg_);
  }

private:
  ::car_msgs::msg::SensorCalibration msg_;
};

class Init_SensorCalibration_mpu6050_mean_gyro_y
{
public:
  explicit Init_SensorCalibration_mpu6050_mean_gyro_y(::car_msgs::msg::SensorCalibration & msg)
  : msg_(msg)
  {}
  Init_SensorCalibration_mpu6050_mean_gyro_z mpu6050_mean_gyro_y(::car_msgs::msg::SensorCalibration::_mpu6050_mean_gyro_y_type arg)
  {
    msg_.mpu6050_mean_gyro_y = std::move(arg);
    return Init_SensorCalibration_mpu6050_mean_gyro_z(msg_);
  }

private:
  ::car_msgs::msg::SensorCalibration msg_;
};

class Init_SensorCalibration_mpu6050_mean_gyro_x
{
public:
  explicit Init_SensorCalibration_mpu6050_mean_gyro_x(::car_msgs::msg::SensorCalibration & msg)
  : msg_(msg)
  {}
  Init_SensorCalibration_mpu6050_mean_gyro_y mpu6050_mean_gyro_x(::car_msgs::msg::SensorCalibration::_mpu6050_mean_gyro_x_type arg)
  {
    msg_.mpu6050_mean_gyro_x = std::move(arg);
    return Init_SensorCalibration_mpu6050_mean_gyro_y(msg_);
  }

private:
  ::car_msgs::msg::SensorCalibration msg_;
};

class Init_SensorCalibration_mpu6050_var_accel_z
{
public:
  explicit Init_SensorCalibration_mpu6050_var_accel_z(::car_msgs::msg::SensorCalibration & msg)
  : msg_(msg)
  {}
  Init_SensorCalibration_mpu6050_mean_gyro_x mpu6050_var_accel_z(::car_msgs::msg::SensorCalibration::_mpu6050_var_accel_z_type arg)
  {
    msg_.mpu6050_var_accel_z = std::move(arg);
    return Init_SensorCalibration_mpu6050_mean_gyro_x(msg_);
  }

private:
  ::car_msgs::msg::SensorCalibration msg_;
};

class Init_SensorCalibration_mpu6050_var_accel_y
{
public:
  explicit Init_SensorCalibration_mpu6050_var_accel_y(::car_msgs::msg::SensorCalibration & msg)
  : msg_(msg)
  {}
  Init_SensorCalibration_mpu6050_var_accel_z mpu6050_var_accel_y(::car_msgs::msg::SensorCalibration::_mpu6050_var_accel_y_type arg)
  {
    msg_.mpu6050_var_accel_y = std::move(arg);
    return Init_SensorCalibration_mpu6050_var_accel_z(msg_);
  }

private:
  ::car_msgs::msg::SensorCalibration msg_;
};

class Init_SensorCalibration_mpu6050_var_accel_x
{
public:
  explicit Init_SensorCalibration_mpu6050_var_accel_x(::car_msgs::msg::SensorCalibration & msg)
  : msg_(msg)
  {}
  Init_SensorCalibration_mpu6050_var_accel_y mpu6050_var_accel_x(::car_msgs::msg::SensorCalibration::_mpu6050_var_accel_x_type arg)
  {
    msg_.mpu6050_var_accel_x = std::move(arg);
    return Init_SensorCalibration_mpu6050_var_accel_y(msg_);
  }

private:
  ::car_msgs::msg::SensorCalibration msg_;
};

class Init_SensorCalibration_mpu6050_mean_accel_z
{
public:
  explicit Init_SensorCalibration_mpu6050_mean_accel_z(::car_msgs::msg::SensorCalibration & msg)
  : msg_(msg)
  {}
  Init_SensorCalibration_mpu6050_var_accel_x mpu6050_mean_accel_z(::car_msgs::msg::SensorCalibration::_mpu6050_mean_accel_z_type arg)
  {
    msg_.mpu6050_mean_accel_z = std::move(arg);
    return Init_SensorCalibration_mpu6050_var_accel_x(msg_);
  }

private:
  ::car_msgs::msg::SensorCalibration msg_;
};

class Init_SensorCalibration_mpu6050_mean_accel_y
{
public:
  explicit Init_SensorCalibration_mpu6050_mean_accel_y(::car_msgs::msg::SensorCalibration & msg)
  : msg_(msg)
  {}
  Init_SensorCalibration_mpu6050_mean_accel_z mpu6050_mean_accel_y(::car_msgs::msg::SensorCalibration::_mpu6050_mean_accel_y_type arg)
  {
    msg_.mpu6050_mean_accel_y = std::move(arg);
    return Init_SensorCalibration_mpu6050_mean_accel_z(msg_);
  }

private:
  ::car_msgs::msg::SensorCalibration msg_;
};

class Init_SensorCalibration_mpu6050_mean_accel_x
{
public:
  explicit Init_SensorCalibration_mpu6050_mean_accel_x(::car_msgs::msg::SensorCalibration & msg)
  : msg_(msg)
  {}
  Init_SensorCalibration_mpu6050_mean_accel_y mpu6050_mean_accel_x(::car_msgs::msg::SensorCalibration::_mpu6050_mean_accel_x_type arg)
  {
    msg_.mpu6050_mean_accel_x = std::move(arg);
    return Init_SensorCalibration_mpu6050_mean_accel_y(msg_);
  }

private:
  ::car_msgs::msg::SensorCalibration msg_;
};

class Init_SensorCalibration_is_calibrated
{
public:
  explicit Init_SensorCalibration_is_calibrated(::car_msgs::msg::SensorCalibration & msg)
  : msg_(msg)
  {}
  Init_SensorCalibration_mpu6050_mean_accel_x is_calibrated(::car_msgs::msg::SensorCalibration::_is_calibrated_type arg)
  {
    msg_.is_calibrated = std::move(arg);
    return Init_SensorCalibration_mpu6050_mean_accel_x(msg_);
  }

private:
  ::car_msgs::msg::SensorCalibration msg_;
};

class Init_SensorCalibration_header
{
public:
  Init_SensorCalibration_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SensorCalibration_is_calibrated header(::car_msgs::msg::SensorCalibration::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_SensorCalibration_is_calibrated(msg_);
  }

private:
  ::car_msgs::msg::SensorCalibration msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::car_msgs::msg::SensorCalibration>()
{
  return car_msgs::msg::builder::Init_SensorCalibration_header();
}

}  // namespace car_msgs

#endif  // CAR_MSGS__MSG__DETAIL__SENSOR_CALIBRATION__BUILDER_HPP_
