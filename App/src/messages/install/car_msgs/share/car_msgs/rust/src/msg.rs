#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to car_msgs__msg__SensorMeasurements

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SensorMeasurements {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::SensorMeasurements::default())
  }
}

impl rosidl_runtime_rs::Message for SensorMeasurements {
  type RmwMsg = super::msg::rmw::SensorMeasurements;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        mpu6050_accel_x: msg.mpu6050_accel_x,
        mpu6050_accel_y: msg.mpu6050_accel_y,
        mpu6050_accel_z: msg.mpu6050_accel_z,
        mpu6050_gyro_x: msg.mpu6050_gyro_x,
        mpu6050_gyro_y: msg.mpu6050_gyro_y,
        mpu6050_gyro_z: msg.mpu6050_gyro_z,
        ina219_current: msg.ina219_current,
        ina219_power: msg.ina219_power,
        cjmcu103_angle: msg.cjmcu103_angle,
        cjmcu103_anglespeed: msg.cjmcu103_anglespeed,
        wheelencoder_rotspeed: msg.wheelencoder_rotspeed,
        wheelencoder_translspeed: msg.wheelencoder_translspeed,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      mpu6050_accel_x: msg.mpu6050_accel_x,
      mpu6050_accel_y: msg.mpu6050_accel_y,
      mpu6050_accel_z: msg.mpu6050_accel_z,
      mpu6050_gyro_x: msg.mpu6050_gyro_x,
      mpu6050_gyro_y: msg.mpu6050_gyro_y,
      mpu6050_gyro_z: msg.mpu6050_gyro_z,
      ina219_current: msg.ina219_current,
      ina219_power: msg.ina219_power,
      cjmcu103_angle: msg.cjmcu103_angle,
      cjmcu103_anglespeed: msg.cjmcu103_anglespeed,
      wheelencoder_rotspeed: msg.wheelencoder_rotspeed,
      wheelencoder_translspeed: msg.wheelencoder_translspeed,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      mpu6050_accel_x: msg.mpu6050_accel_x,
      mpu6050_accel_y: msg.mpu6050_accel_y,
      mpu6050_accel_z: msg.mpu6050_accel_z,
      mpu6050_gyro_x: msg.mpu6050_gyro_x,
      mpu6050_gyro_y: msg.mpu6050_gyro_y,
      mpu6050_gyro_z: msg.mpu6050_gyro_z,
      ina219_current: msg.ina219_current,
      ina219_power: msg.ina219_power,
      cjmcu103_angle: msg.cjmcu103_angle,
      cjmcu103_anglespeed: msg.cjmcu103_anglespeed,
      wheelencoder_rotspeed: msg.wheelencoder_rotspeed,
      wheelencoder_translspeed: msg.wheelencoder_translspeed,
    }
  }
}


// Corresponds to car_msgs__msg__SensorCalibration

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SensorCalibration {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::SensorCalibration::default())
  }
}

impl rosidl_runtime_rs::Message for SensorCalibration {
  type RmwMsg = super::msg::rmw::SensorCalibration;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        is_calibrated: msg.is_calibrated,
        mpu6050_mean_accel_x: msg.mpu6050_mean_accel_x,
        mpu6050_mean_accel_y: msg.mpu6050_mean_accel_y,
        mpu6050_mean_accel_z: msg.mpu6050_mean_accel_z,
        mpu6050_var_accel_x: msg.mpu6050_var_accel_x,
        mpu6050_var_accel_y: msg.mpu6050_var_accel_y,
        mpu6050_var_accel_z: msg.mpu6050_var_accel_z,
        mpu6050_mean_gyro_x: msg.mpu6050_mean_gyro_x,
        mpu6050_mean_gyro_y: msg.mpu6050_mean_gyro_y,
        mpu6050_mean_gyro_z: msg.mpu6050_mean_gyro_z,
        mpu6050_var_gyro_x: msg.mpu6050_var_gyro_x,
        mpu6050_var_gyro_y: msg.mpu6050_var_gyro_y,
        mpu6050_var_gyro_z: msg.mpu6050_var_gyro_z,
        cjmcu103_mean_angle: msg.cjmcu103_mean_angle,
        cjmcu103_var_angle: msg.cjmcu103_var_angle,
        cjmcu103_mean_anglespeed: msg.cjmcu103_mean_anglespeed,
        cjmcu103_var_anglespeed: msg.cjmcu103_var_anglespeed,
        wheelencoder_var_rotspeed: msg.wheelencoder_var_rotspeed,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      is_calibrated: msg.is_calibrated,
      mpu6050_mean_accel_x: msg.mpu6050_mean_accel_x,
      mpu6050_mean_accel_y: msg.mpu6050_mean_accel_y,
      mpu6050_mean_accel_z: msg.mpu6050_mean_accel_z,
      mpu6050_var_accel_x: msg.mpu6050_var_accel_x,
      mpu6050_var_accel_y: msg.mpu6050_var_accel_y,
      mpu6050_var_accel_z: msg.mpu6050_var_accel_z,
      mpu6050_mean_gyro_x: msg.mpu6050_mean_gyro_x,
      mpu6050_mean_gyro_y: msg.mpu6050_mean_gyro_y,
      mpu6050_mean_gyro_z: msg.mpu6050_mean_gyro_z,
      mpu6050_var_gyro_x: msg.mpu6050_var_gyro_x,
      mpu6050_var_gyro_y: msg.mpu6050_var_gyro_y,
      mpu6050_var_gyro_z: msg.mpu6050_var_gyro_z,
      cjmcu103_mean_angle: msg.cjmcu103_mean_angle,
      cjmcu103_var_angle: msg.cjmcu103_var_angle,
      cjmcu103_mean_anglespeed: msg.cjmcu103_mean_anglespeed,
      cjmcu103_var_anglespeed: msg.cjmcu103_var_anglespeed,
      wheelencoder_var_rotspeed: msg.wheelencoder_var_rotspeed,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      is_calibrated: msg.is_calibrated,
      mpu6050_mean_accel_x: msg.mpu6050_mean_accel_x,
      mpu6050_mean_accel_y: msg.mpu6050_mean_accel_y,
      mpu6050_mean_accel_z: msg.mpu6050_mean_accel_z,
      mpu6050_var_accel_x: msg.mpu6050_var_accel_x,
      mpu6050_var_accel_y: msg.mpu6050_var_accel_y,
      mpu6050_var_accel_z: msg.mpu6050_var_accel_z,
      mpu6050_mean_gyro_x: msg.mpu6050_mean_gyro_x,
      mpu6050_mean_gyro_y: msg.mpu6050_mean_gyro_y,
      mpu6050_mean_gyro_z: msg.mpu6050_mean_gyro_z,
      mpu6050_var_gyro_x: msg.mpu6050_var_gyro_x,
      mpu6050_var_gyro_y: msg.mpu6050_var_gyro_y,
      mpu6050_var_gyro_z: msg.mpu6050_var_gyro_z,
      cjmcu103_mean_angle: msg.cjmcu103_mean_angle,
      cjmcu103_var_angle: msg.cjmcu103_var_angle,
      cjmcu103_mean_anglespeed: msg.cjmcu103_mean_anglespeed,
      cjmcu103_var_anglespeed: msg.cjmcu103_var_anglespeed,
      wheelencoder_var_rotspeed: msg.wheelencoder_var_rotspeed,
    }
  }
}


// Corresponds to car_msgs__msg__VehicleState

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct VehicleState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::VehicleState::default())
  }
}

impl rosidl_runtime_rs::Message for VehicleState {
  type RmwMsg = super::msg::rmw::VehicleState;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        pos_x: msg.pos_x,
        pos_y: msg.pos_y,
        speed: msg.speed,
        yaw: msg.yaw,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      pos_x: msg.pos_x,
      pos_y: msg.pos_y,
      speed: msg.speed,
      yaw: msg.yaw,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      pos_x: msg.pos_x,
      pos_y: msg.pos_y,
      speed: msg.speed,
      yaw: msg.yaw,
    }
  }
}


// Corresponds to car_msgs__msg__MotionControl

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MotionControl {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub yaw_rate: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub speed: f32,

}



impl Default for MotionControl {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::MotionControl::default())
  }
}

impl rosidl_runtime_rs::Message for MotionControl {
  type RmwMsg = super::msg::rmw::MotionControl;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        yaw_rate: msg.yaw_rate,
        speed: msg.speed,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      yaw_rate: msg.yaw_rate,
      speed: msg.speed,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      yaw_rate: msg.yaw_rate,
      speed: msg.speed,
    }
  }
}


// Corresponds to car_msgs__msg__NodeState

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct NodeState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub localizer_is_ready: bool,

}



impl Default for NodeState {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::NodeState::default())
  }
}

impl rosidl_runtime_rs::Message for NodeState {
  type RmwMsg = super::msg::rmw::NodeState;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        localizer_is_ready: msg.localizer_is_ready,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      localizer_is_ready: msg.localizer_is_ready,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      localizer_is_ready: msg.localizer_is_ready,
    }
  }
}


// Corresponds to car_msgs__msg__DebugController

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DebugController {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


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
    pub idx_closest_node: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub cte: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub heading_error: f32,

}



impl Default for DebugController {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::DebugController::default())
  }
}

impl rosidl_runtime_rs::Message for DebugController {
  type RmwMsg = super::msg::rmw::DebugController;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        yaw_rate: msg.yaw_rate,
        yaw: msg.yaw,
        cn_yaw: msg.cn_yaw,
        speed: msg.speed,
        steering_angle: msg.steering_angle,
        idx_closest_node: msg.idx_closest_node,
        cte: msg.cte,
        heading_error: msg.heading_error,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      yaw_rate: msg.yaw_rate,
      yaw: msg.yaw,
      cn_yaw: msg.cn_yaw,
      speed: msg.speed,
      steering_angle: msg.steering_angle,
      idx_closest_node: msg.idx_closest_node,
      cte: msg.cte,
      heading_error: msg.heading_error,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      yaw_rate: msg.yaw_rate,
      yaw: msg.yaw,
      cn_yaw: msg.cn_yaw,
      speed: msg.speed,
      steering_angle: msg.steering_angle,
      idx_closest_node: msg.idx_closest_node,
      cte: msg.cte,
      heading_error: msg.heading_error,
    }
  }
}


// Corresponds to car_msgs__msg__PathNode

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PathNode {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::PathNode::default())
  }
}

impl rosidl_runtime_rs::Message for PathNode {
  type RmwMsg = super::msg::rmw::PathNode;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        x: msg.x,
        y: msg.y,
        th: msg.th,
        idx: msg.idx,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      x: msg.x,
      y: msg.y,
      th: msg.th,
      idx: msg.idx,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      x: msg.x,
      y: msg.y,
      th: msg.th,
      idx: msg.idx,
    }
  }
}


// Corresponds to car_msgs__msg__DebugPlanner

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DebugPlanner {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub length_path: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub idx_update_node: i32,

}



impl Default for DebugPlanner {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::DebugPlanner::default())
  }
}

impl rosidl_runtime_rs::Message for DebugPlanner {
  type RmwMsg = super::msg::rmw::DebugPlanner;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        length_path: msg.length_path,
        idx_update_node: msg.idx_update_node,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      length_path: msg.length_path,
      idx_update_node: msg.idx_update_node,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      length_path: msg.length_path,
      idx_update_node: msg.idx_update_node,
    }
  }
}


