#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "car_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__car_msgs__msg__SensorMeasurements() -> *const std::ffi::c_void;
}

#[link(name = "car_msgs__rosidl_generator_c")]
extern "C" {
    fn car_msgs__msg__SensorMeasurements__init(msg: *mut SensorMeasurements) -> bool;
    fn car_msgs__msg__SensorMeasurements__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SensorMeasurements>, size: usize) -> bool;
    fn car_msgs__msg__SensorMeasurements__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SensorMeasurements>);
    fn car_msgs__msg__SensorMeasurements__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SensorMeasurements>, out_seq: *mut rosidl_runtime_rs::Sequence<SensorMeasurements>) -> bool;
}

// Corresponds to car_msgs__msg__SensorMeasurements
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SensorMeasurements {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mpu6050_accel_x: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mpu6050_accel_y: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mpu6050_accel_z: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mpu6050_gyro_x: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mpu6050_gyro_y: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mpu6050_gyro_z: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub ina219_current: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub ina219_power: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub cjmcu103_angle: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub cjmcu103_anglespeed: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub wheelencoder_rotspeed: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub wheelencoder_translspeed: f32,

}



impl Default for SensorMeasurements {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !car_msgs__msg__SensorMeasurements__init(&mut msg as *mut _) {
        panic!("Call to car_msgs__msg__SensorMeasurements__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SensorMeasurements {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { car_msgs__msg__SensorMeasurements__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { car_msgs__msg__SensorMeasurements__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { car_msgs__msg__SensorMeasurements__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SensorMeasurements {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SensorMeasurements where Self: Sized {
  const TYPE_NAME: &'static str = "car_msgs/msg/SensorMeasurements";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__car_msgs__msg__SensorMeasurements() }
  }
}


#[link(name = "car_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__car_msgs__msg__SensorCalibration() -> *const std::ffi::c_void;
}

#[link(name = "car_msgs__rosidl_generator_c")]
extern "C" {
    fn car_msgs__msg__SensorCalibration__init(msg: *mut SensorCalibration) -> bool;
    fn car_msgs__msg__SensorCalibration__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SensorCalibration>, size: usize) -> bool;
    fn car_msgs__msg__SensorCalibration__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SensorCalibration>);
    fn car_msgs__msg__SensorCalibration__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SensorCalibration>, out_seq: *mut rosidl_runtime_rs::Sequence<SensorCalibration>) -> bool;
}

// Corresponds to car_msgs__msg__SensorCalibration
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SensorCalibration {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub is_calibrated: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mpu6050_mean_accel_x: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mpu6050_mean_accel_y: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mpu6050_mean_accel_z: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mpu6050_var_accel_x: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mpu6050_var_accel_y: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mpu6050_var_accel_z: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mpu6050_mean_gyro_x: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mpu6050_mean_gyro_y: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mpu6050_mean_gyro_z: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mpu6050_var_gyro_x: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mpu6050_var_gyro_y: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mpu6050_var_gyro_z: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub cjmcu103_mean_angle: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub cjmcu103_var_angle: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub cjmcu103_mean_anglespeed: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub cjmcu103_var_anglespeed: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub wheelencoder_var_rotspeed: f32,

}



impl Default for SensorCalibration {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !car_msgs__msg__SensorCalibration__init(&mut msg as *mut _) {
        panic!("Call to car_msgs__msg__SensorCalibration__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SensorCalibration {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { car_msgs__msg__SensorCalibration__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { car_msgs__msg__SensorCalibration__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { car_msgs__msg__SensorCalibration__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SensorCalibration {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SensorCalibration where Self: Sized {
  const TYPE_NAME: &'static str = "car_msgs/msg/SensorCalibration";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__car_msgs__msg__SensorCalibration() }
  }
}


#[link(name = "car_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__car_msgs__msg__VehicleState() -> *const std::ffi::c_void;
}

#[link(name = "car_msgs__rosidl_generator_c")]
extern "C" {
    fn car_msgs__msg__VehicleState__init(msg: *mut VehicleState) -> bool;
    fn car_msgs__msg__VehicleState__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<VehicleState>, size: usize) -> bool;
    fn car_msgs__msg__VehicleState__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<VehicleState>);
    fn car_msgs__msg__VehicleState__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<VehicleState>, out_seq: *mut rosidl_runtime_rs::Sequence<VehicleState>) -> bool;
}

// Corresponds to car_msgs__msg__VehicleState
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct VehicleState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pos_x: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pos_y: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub speed: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub yaw: f32,

}



impl Default for VehicleState {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !car_msgs__msg__VehicleState__init(&mut msg as *mut _) {
        panic!("Call to car_msgs__msg__VehicleState__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for VehicleState {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { car_msgs__msg__VehicleState__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { car_msgs__msg__VehicleState__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { car_msgs__msg__VehicleState__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for VehicleState {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for VehicleState where Self: Sized {
  const TYPE_NAME: &'static str = "car_msgs/msg/VehicleState";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__car_msgs__msg__VehicleState() }
  }
}


#[link(name = "car_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__car_msgs__msg__MotionControl() -> *const std::ffi::c_void;
}

#[link(name = "car_msgs__rosidl_generator_c")]
extern "C" {
    fn car_msgs__msg__MotionControl__init(msg: *mut MotionControl) -> bool;
    fn car_msgs__msg__MotionControl__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<MotionControl>, size: usize) -> bool;
    fn car_msgs__msg__MotionControl__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<MotionControl>);
    fn car_msgs__msg__MotionControl__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<MotionControl>, out_seq: *mut rosidl_runtime_rs::Sequence<MotionControl>) -> bool;
}

// Corresponds to car_msgs__msg__MotionControl
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MotionControl {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub yaw_rate: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub speed: f32,

}



impl Default for MotionControl {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !car_msgs__msg__MotionControl__init(&mut msg as *mut _) {
        panic!("Call to car_msgs__msg__MotionControl__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for MotionControl {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { car_msgs__msg__MotionControl__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { car_msgs__msg__MotionControl__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { car_msgs__msg__MotionControl__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for MotionControl {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for MotionControl where Self: Sized {
  const TYPE_NAME: &'static str = "car_msgs/msg/MotionControl";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__car_msgs__msg__MotionControl() }
  }
}


#[link(name = "car_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__car_msgs__msg__NodeState() -> *const std::ffi::c_void;
}

#[link(name = "car_msgs__rosidl_generator_c")]
extern "C" {
    fn car_msgs__msg__NodeState__init(msg: *mut NodeState) -> bool;
    fn car_msgs__msg__NodeState__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<NodeState>, size: usize) -> bool;
    fn car_msgs__msg__NodeState__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<NodeState>);
    fn car_msgs__msg__NodeState__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<NodeState>, out_seq: *mut rosidl_runtime_rs::Sequence<NodeState>) -> bool;
}

// Corresponds to car_msgs__msg__NodeState
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct NodeState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub localizer_is_ready: bool,

}



impl Default for NodeState {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !car_msgs__msg__NodeState__init(&mut msg as *mut _) {
        panic!("Call to car_msgs__msg__NodeState__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for NodeState {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { car_msgs__msg__NodeState__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { car_msgs__msg__NodeState__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { car_msgs__msg__NodeState__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for NodeState {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for NodeState where Self: Sized {
  const TYPE_NAME: &'static str = "car_msgs/msg/NodeState";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__car_msgs__msg__NodeState() }
  }
}


#[link(name = "car_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__car_msgs__msg__DebugController() -> *const std::ffi::c_void;
}

#[link(name = "car_msgs__rosidl_generator_c")]
extern "C" {
    fn car_msgs__msg__DebugController__init(msg: *mut DebugController) -> bool;
    fn car_msgs__msg__DebugController__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DebugController>, size: usize) -> bool;
    fn car_msgs__msg__DebugController__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DebugController>);
    fn car_msgs__msg__DebugController__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DebugController>, out_seq: *mut rosidl_runtime_rs::Sequence<DebugController>) -> bool;
}

// Corresponds to car_msgs__msg__DebugController
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DebugController {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub yaw_rate: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub yaw: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub cn_yaw: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub speed: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub steering_angle: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pdx_cnode: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub cte: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub heading_error: f32,

}



impl Default for DebugController {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !car_msgs__msg__DebugController__init(&mut msg as *mut _) {
        panic!("Call to car_msgs__msg__DebugController__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DebugController {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { car_msgs__msg__DebugController__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { car_msgs__msg__DebugController__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { car_msgs__msg__DebugController__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DebugController {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DebugController where Self: Sized {
  const TYPE_NAME: &'static str = "car_msgs/msg/DebugController";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__car_msgs__msg__DebugController() }
  }
}


#[link(name = "car_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__car_msgs__msg__PathNode() -> *const std::ffi::c_void;
}

#[link(name = "car_msgs__rosidl_generator_c")]
extern "C" {
    fn car_msgs__msg__PathNode__init(msg: *mut PathNode) -> bool;
    fn car_msgs__msg__PathNode__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PathNode>, size: usize) -> bool;
    fn car_msgs__msg__PathNode__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PathNode>);
    fn car_msgs__msg__PathNode__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PathNode>, out_seq: *mut rosidl_runtime_rs::Sequence<PathNode>) -> bool;
}

// Corresponds to car_msgs__msg__PathNode
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PathNode {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub x: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub y: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub th: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub idx: i32,

}



impl Default for PathNode {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !car_msgs__msg__PathNode__init(&mut msg as *mut _) {
        panic!("Call to car_msgs__msg__PathNode__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PathNode {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { car_msgs__msg__PathNode__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { car_msgs__msg__PathNode__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { car_msgs__msg__PathNode__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PathNode {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PathNode where Self: Sized {
  const TYPE_NAME: &'static str = "car_msgs/msg/PathNode";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__car_msgs__msg__PathNode() }
  }
}


