// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from car_msgs:msg/SensorCalibration.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/sensor_calibration.hpp"


#ifndef CAR_MSGS__MSG__DETAIL__SENSOR_CALIBRATION__STRUCT_HPP_
#define CAR_MSGS__MSG__DETAIL__SENSOR_CALIBRATION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__car_msgs__msg__SensorCalibration __attribute__((deprecated))
#else
# define DEPRECATED__car_msgs__msg__SensorCalibration __declspec(deprecated)
#endif

namespace car_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SensorCalibration_
{
  using Type = SensorCalibration_<ContainerAllocator>;

  explicit SensorCalibration_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->is_calibrated = false;
      this->mpu6050_mean_accel_x = 0.0f;
      this->mpu6050_mean_accel_y = 0.0f;
      this->mpu6050_mean_accel_z = 0.0f;
      this->mpu6050_var_accel_x = 0.0f;
      this->mpu6050_var_accel_y = 0.0f;
      this->mpu6050_var_accel_z = 0.0f;
      this->mpu6050_mean_gyro_x = 0.0f;
      this->mpu6050_mean_gyro_y = 0.0f;
      this->mpu6050_mean_gyro_z = 0.0f;
      this->mpu6050_var_gyro_x = 0.0f;
      this->mpu6050_var_gyro_y = 0.0f;
      this->mpu6050_var_gyro_z = 0.0f;
      this->cjmcu103_mean_angle = 0.0f;
      this->cjmcu103_var_angle = 0.0f;
      this->cjmcu103_mean_anglespeed = 0.0f;
      this->cjmcu103_var_anglespeed = 0.0f;
      this->wheelencoder_var_rotspeed = 0.0f;
    }
  }

  explicit SensorCalibration_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->is_calibrated = false;
      this->mpu6050_mean_accel_x = 0.0f;
      this->mpu6050_mean_accel_y = 0.0f;
      this->mpu6050_mean_accel_z = 0.0f;
      this->mpu6050_var_accel_x = 0.0f;
      this->mpu6050_var_accel_y = 0.0f;
      this->mpu6050_var_accel_z = 0.0f;
      this->mpu6050_mean_gyro_x = 0.0f;
      this->mpu6050_mean_gyro_y = 0.0f;
      this->mpu6050_mean_gyro_z = 0.0f;
      this->mpu6050_var_gyro_x = 0.0f;
      this->mpu6050_var_gyro_y = 0.0f;
      this->mpu6050_var_gyro_z = 0.0f;
      this->cjmcu103_mean_angle = 0.0f;
      this->cjmcu103_var_angle = 0.0f;
      this->cjmcu103_mean_anglespeed = 0.0f;
      this->cjmcu103_var_anglespeed = 0.0f;
      this->wheelencoder_var_rotspeed = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _is_calibrated_type =
    bool;
  _is_calibrated_type is_calibrated;
  using _mpu6050_mean_accel_x_type =
    float;
  _mpu6050_mean_accel_x_type mpu6050_mean_accel_x;
  using _mpu6050_mean_accel_y_type =
    float;
  _mpu6050_mean_accel_y_type mpu6050_mean_accel_y;
  using _mpu6050_mean_accel_z_type =
    float;
  _mpu6050_mean_accel_z_type mpu6050_mean_accel_z;
  using _mpu6050_var_accel_x_type =
    float;
  _mpu6050_var_accel_x_type mpu6050_var_accel_x;
  using _mpu6050_var_accel_y_type =
    float;
  _mpu6050_var_accel_y_type mpu6050_var_accel_y;
  using _mpu6050_var_accel_z_type =
    float;
  _mpu6050_var_accel_z_type mpu6050_var_accel_z;
  using _mpu6050_mean_gyro_x_type =
    float;
  _mpu6050_mean_gyro_x_type mpu6050_mean_gyro_x;
  using _mpu6050_mean_gyro_y_type =
    float;
  _mpu6050_mean_gyro_y_type mpu6050_mean_gyro_y;
  using _mpu6050_mean_gyro_z_type =
    float;
  _mpu6050_mean_gyro_z_type mpu6050_mean_gyro_z;
  using _mpu6050_var_gyro_x_type =
    float;
  _mpu6050_var_gyro_x_type mpu6050_var_gyro_x;
  using _mpu6050_var_gyro_y_type =
    float;
  _mpu6050_var_gyro_y_type mpu6050_var_gyro_y;
  using _mpu6050_var_gyro_z_type =
    float;
  _mpu6050_var_gyro_z_type mpu6050_var_gyro_z;
  using _cjmcu103_mean_angle_type =
    float;
  _cjmcu103_mean_angle_type cjmcu103_mean_angle;
  using _cjmcu103_var_angle_type =
    float;
  _cjmcu103_var_angle_type cjmcu103_var_angle;
  using _cjmcu103_mean_anglespeed_type =
    float;
  _cjmcu103_mean_anglespeed_type cjmcu103_mean_anglespeed;
  using _cjmcu103_var_anglespeed_type =
    float;
  _cjmcu103_var_anglespeed_type cjmcu103_var_anglespeed;
  using _wheelencoder_var_rotspeed_type =
    float;
  _wheelencoder_var_rotspeed_type wheelencoder_var_rotspeed;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__is_calibrated(
    const bool & _arg)
  {
    this->is_calibrated = _arg;
    return *this;
  }
  Type & set__mpu6050_mean_accel_x(
    const float & _arg)
  {
    this->mpu6050_mean_accel_x = _arg;
    return *this;
  }
  Type & set__mpu6050_mean_accel_y(
    const float & _arg)
  {
    this->mpu6050_mean_accel_y = _arg;
    return *this;
  }
  Type & set__mpu6050_mean_accel_z(
    const float & _arg)
  {
    this->mpu6050_mean_accel_z = _arg;
    return *this;
  }
  Type & set__mpu6050_var_accel_x(
    const float & _arg)
  {
    this->mpu6050_var_accel_x = _arg;
    return *this;
  }
  Type & set__mpu6050_var_accel_y(
    const float & _arg)
  {
    this->mpu6050_var_accel_y = _arg;
    return *this;
  }
  Type & set__mpu6050_var_accel_z(
    const float & _arg)
  {
    this->mpu6050_var_accel_z = _arg;
    return *this;
  }
  Type & set__mpu6050_mean_gyro_x(
    const float & _arg)
  {
    this->mpu6050_mean_gyro_x = _arg;
    return *this;
  }
  Type & set__mpu6050_mean_gyro_y(
    const float & _arg)
  {
    this->mpu6050_mean_gyro_y = _arg;
    return *this;
  }
  Type & set__mpu6050_mean_gyro_z(
    const float & _arg)
  {
    this->mpu6050_mean_gyro_z = _arg;
    return *this;
  }
  Type & set__mpu6050_var_gyro_x(
    const float & _arg)
  {
    this->mpu6050_var_gyro_x = _arg;
    return *this;
  }
  Type & set__mpu6050_var_gyro_y(
    const float & _arg)
  {
    this->mpu6050_var_gyro_y = _arg;
    return *this;
  }
  Type & set__mpu6050_var_gyro_z(
    const float & _arg)
  {
    this->mpu6050_var_gyro_z = _arg;
    return *this;
  }
  Type & set__cjmcu103_mean_angle(
    const float & _arg)
  {
    this->cjmcu103_mean_angle = _arg;
    return *this;
  }
  Type & set__cjmcu103_var_angle(
    const float & _arg)
  {
    this->cjmcu103_var_angle = _arg;
    return *this;
  }
  Type & set__cjmcu103_mean_anglespeed(
    const float & _arg)
  {
    this->cjmcu103_mean_anglespeed = _arg;
    return *this;
  }
  Type & set__cjmcu103_var_anglespeed(
    const float & _arg)
  {
    this->cjmcu103_var_anglespeed = _arg;
    return *this;
  }
  Type & set__wheelencoder_var_rotspeed(
    const float & _arg)
  {
    this->wheelencoder_var_rotspeed = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    car_msgs::msg::SensorCalibration_<ContainerAllocator> *;
  using ConstRawPtr =
    const car_msgs::msg::SensorCalibration_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<car_msgs::msg::SensorCalibration_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<car_msgs::msg::SensorCalibration_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      car_msgs::msg::SensorCalibration_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<car_msgs::msg::SensorCalibration_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      car_msgs::msg::SensorCalibration_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<car_msgs::msg::SensorCalibration_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<car_msgs::msg::SensorCalibration_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<car_msgs::msg::SensorCalibration_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__car_msgs__msg__SensorCalibration
    std::shared_ptr<car_msgs::msg::SensorCalibration_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__car_msgs__msg__SensorCalibration
    std::shared_ptr<car_msgs::msg::SensorCalibration_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SensorCalibration_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->is_calibrated != other.is_calibrated) {
      return false;
    }
    if (this->mpu6050_mean_accel_x != other.mpu6050_mean_accel_x) {
      return false;
    }
    if (this->mpu6050_mean_accel_y != other.mpu6050_mean_accel_y) {
      return false;
    }
    if (this->mpu6050_mean_accel_z != other.mpu6050_mean_accel_z) {
      return false;
    }
    if (this->mpu6050_var_accel_x != other.mpu6050_var_accel_x) {
      return false;
    }
    if (this->mpu6050_var_accel_y != other.mpu6050_var_accel_y) {
      return false;
    }
    if (this->mpu6050_var_accel_z != other.mpu6050_var_accel_z) {
      return false;
    }
    if (this->mpu6050_mean_gyro_x != other.mpu6050_mean_gyro_x) {
      return false;
    }
    if (this->mpu6050_mean_gyro_y != other.mpu6050_mean_gyro_y) {
      return false;
    }
    if (this->mpu6050_mean_gyro_z != other.mpu6050_mean_gyro_z) {
      return false;
    }
    if (this->mpu6050_var_gyro_x != other.mpu6050_var_gyro_x) {
      return false;
    }
    if (this->mpu6050_var_gyro_y != other.mpu6050_var_gyro_y) {
      return false;
    }
    if (this->mpu6050_var_gyro_z != other.mpu6050_var_gyro_z) {
      return false;
    }
    if (this->cjmcu103_mean_angle != other.cjmcu103_mean_angle) {
      return false;
    }
    if (this->cjmcu103_var_angle != other.cjmcu103_var_angle) {
      return false;
    }
    if (this->cjmcu103_mean_anglespeed != other.cjmcu103_mean_anglespeed) {
      return false;
    }
    if (this->cjmcu103_var_anglespeed != other.cjmcu103_var_anglespeed) {
      return false;
    }
    if (this->wheelencoder_var_rotspeed != other.wheelencoder_var_rotspeed) {
      return false;
    }
    return true;
  }
  bool operator!=(const SensorCalibration_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SensorCalibration_

// alias to use template instance with default allocator
using SensorCalibration =
  car_msgs::msg::SensorCalibration_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace car_msgs

#endif  // CAR_MSGS__MSG__DETAIL__SENSOR_CALIBRATION__STRUCT_HPP_
