// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from car_msgs:msg/SensorMeasurements.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "car_msgs/msg/sensor_measurements.hpp"


#ifndef CAR_MSGS__MSG__DETAIL__SENSOR_MEASUREMENTS__STRUCT_HPP_
#define CAR_MSGS__MSG__DETAIL__SENSOR_MEASUREMENTS__STRUCT_HPP_

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
# define DEPRECATED__car_msgs__msg__SensorMeasurements __attribute__((deprecated))
#else
# define DEPRECATED__car_msgs__msg__SensorMeasurements __declspec(deprecated)
#endif

namespace car_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SensorMeasurements_
{
  using Type = SensorMeasurements_<ContainerAllocator>;

  explicit SensorMeasurements_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mpu6050_accel_x = 0.0f;
      this->mpu6050_accel_y = 0.0f;
      this->mpu6050_accel_z = 0.0f;
      this->mpu6050_gyro_x = 0.0f;
      this->mpu6050_gyro_y = 0.0f;
      this->mpu6050_gyro_z = 0.0f;
      this->ina219_current = 0.0f;
      this->ina219_power = 0.0f;
      this->cjmcu103_angle = 0.0f;
      this->cjmcu103_anglespeed = 0.0f;
      this->wheelencoder_rotspeed = 0.0f;
      this->wheelencoder_translspeed = 0.0f;
    }
  }

  explicit SensorMeasurements_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mpu6050_accel_x = 0.0f;
      this->mpu6050_accel_y = 0.0f;
      this->mpu6050_accel_z = 0.0f;
      this->mpu6050_gyro_x = 0.0f;
      this->mpu6050_gyro_y = 0.0f;
      this->mpu6050_gyro_z = 0.0f;
      this->ina219_current = 0.0f;
      this->ina219_power = 0.0f;
      this->cjmcu103_angle = 0.0f;
      this->cjmcu103_anglespeed = 0.0f;
      this->wheelencoder_rotspeed = 0.0f;
      this->wheelencoder_translspeed = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _mpu6050_accel_x_type =
    float;
  _mpu6050_accel_x_type mpu6050_accel_x;
  using _mpu6050_accel_y_type =
    float;
  _mpu6050_accel_y_type mpu6050_accel_y;
  using _mpu6050_accel_z_type =
    float;
  _mpu6050_accel_z_type mpu6050_accel_z;
  using _mpu6050_gyro_x_type =
    float;
  _mpu6050_gyro_x_type mpu6050_gyro_x;
  using _mpu6050_gyro_y_type =
    float;
  _mpu6050_gyro_y_type mpu6050_gyro_y;
  using _mpu6050_gyro_z_type =
    float;
  _mpu6050_gyro_z_type mpu6050_gyro_z;
  using _ina219_current_type =
    float;
  _ina219_current_type ina219_current;
  using _ina219_power_type =
    float;
  _ina219_power_type ina219_power;
  using _cjmcu103_angle_type =
    float;
  _cjmcu103_angle_type cjmcu103_angle;
  using _cjmcu103_anglespeed_type =
    float;
  _cjmcu103_anglespeed_type cjmcu103_anglespeed;
  using _wheelencoder_rotspeed_type =
    float;
  _wheelencoder_rotspeed_type wheelencoder_rotspeed;
  using _wheelencoder_translspeed_type =
    float;
  _wheelencoder_translspeed_type wheelencoder_translspeed;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__mpu6050_accel_x(
    const float & _arg)
  {
    this->mpu6050_accel_x = _arg;
    return *this;
  }
  Type & set__mpu6050_accel_y(
    const float & _arg)
  {
    this->mpu6050_accel_y = _arg;
    return *this;
  }
  Type & set__mpu6050_accel_z(
    const float & _arg)
  {
    this->mpu6050_accel_z = _arg;
    return *this;
  }
  Type & set__mpu6050_gyro_x(
    const float & _arg)
  {
    this->mpu6050_gyro_x = _arg;
    return *this;
  }
  Type & set__mpu6050_gyro_y(
    const float & _arg)
  {
    this->mpu6050_gyro_y = _arg;
    return *this;
  }
  Type & set__mpu6050_gyro_z(
    const float & _arg)
  {
    this->mpu6050_gyro_z = _arg;
    return *this;
  }
  Type & set__ina219_current(
    const float & _arg)
  {
    this->ina219_current = _arg;
    return *this;
  }
  Type & set__ina219_power(
    const float & _arg)
  {
    this->ina219_power = _arg;
    return *this;
  }
  Type & set__cjmcu103_angle(
    const float & _arg)
  {
    this->cjmcu103_angle = _arg;
    return *this;
  }
  Type & set__cjmcu103_anglespeed(
    const float & _arg)
  {
    this->cjmcu103_anglespeed = _arg;
    return *this;
  }
  Type & set__wheelencoder_rotspeed(
    const float & _arg)
  {
    this->wheelencoder_rotspeed = _arg;
    return *this;
  }
  Type & set__wheelencoder_translspeed(
    const float & _arg)
  {
    this->wheelencoder_translspeed = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    car_msgs::msg::SensorMeasurements_<ContainerAllocator> *;
  using ConstRawPtr =
    const car_msgs::msg::SensorMeasurements_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<car_msgs::msg::SensorMeasurements_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<car_msgs::msg::SensorMeasurements_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      car_msgs::msg::SensorMeasurements_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<car_msgs::msg::SensorMeasurements_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      car_msgs::msg::SensorMeasurements_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<car_msgs::msg::SensorMeasurements_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<car_msgs::msg::SensorMeasurements_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<car_msgs::msg::SensorMeasurements_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__car_msgs__msg__SensorMeasurements
    std::shared_ptr<car_msgs::msg::SensorMeasurements_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__car_msgs__msg__SensorMeasurements
    std::shared_ptr<car_msgs::msg::SensorMeasurements_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SensorMeasurements_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->mpu6050_accel_x != other.mpu6050_accel_x) {
      return false;
    }
    if (this->mpu6050_accel_y != other.mpu6050_accel_y) {
      return false;
    }
    if (this->mpu6050_accel_z != other.mpu6050_accel_z) {
      return false;
    }
    if (this->mpu6050_gyro_x != other.mpu6050_gyro_x) {
      return false;
    }
    if (this->mpu6050_gyro_y != other.mpu6050_gyro_y) {
      return false;
    }
    if (this->mpu6050_gyro_z != other.mpu6050_gyro_z) {
      return false;
    }
    if (this->ina219_current != other.ina219_current) {
      return false;
    }
    if (this->ina219_power != other.ina219_power) {
      return false;
    }
    if (this->cjmcu103_angle != other.cjmcu103_angle) {
      return false;
    }
    if (this->cjmcu103_anglespeed != other.cjmcu103_anglespeed) {
      return false;
    }
    if (this->wheelencoder_rotspeed != other.wheelencoder_rotspeed) {
      return false;
    }
    if (this->wheelencoder_translspeed != other.wheelencoder_translspeed) {
      return false;
    }
    return true;
  }
  bool operator!=(const SensorMeasurements_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SensorMeasurements_

// alias to use template instance with default allocator
using SensorMeasurements =
  car_msgs::msg::SensorMeasurements_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace car_msgs

#endif  // CAR_MSGS__MSG__DETAIL__SENSOR_MEASUREMENTS__STRUCT_HPP_
