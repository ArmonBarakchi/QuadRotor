#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to quadrotor_msgs__msg__DroneState

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DroneState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub position: [f64; 3],


    // This member is not documented.
    #[allow(missing_docs)]
    pub velocity: [f64; 3],


    // This member is not documented.
    #[allow(missing_docs)]
    pub quaternion: [f64; 4],


    // This member is not documented.
    #[allow(missing_docs)]
    pub omega: [f64; 3],


    // This member is not documented.
    #[allow(missing_docs)]
    pub gyro_bias: [f64; 3],


    // This member is not documented.
    #[allow(missing_docs)]
    pub accel_bias: [f64; 3],

}



impl Default for DroneState {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::DroneState::default())
  }
}

impl rosidl_runtime_rs::Message for DroneState {
  type RmwMsg = super::msg::rmw::DroneState;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        position: msg.position,
        velocity: msg.velocity,
        quaternion: msg.quaternion,
        omega: msg.omega,
        gyro_bias: msg.gyro_bias,
        accel_bias: msg.accel_bias,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        position: msg.position,
        velocity: msg.velocity,
        quaternion: msg.quaternion,
        omega: msg.omega,
        gyro_bias: msg.gyro_bias,
        accel_bias: msg.accel_bias,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      position: msg.position,
      velocity: msg.velocity,
      quaternion: msg.quaternion,
      omega: msg.omega,
      gyro_bias: msg.gyro_bias,
      accel_bias: msg.accel_bias,
    }
  }
}


// Corresponds to quadrotor_msgs__msg__DroneControl

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DroneControl {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub force_des: [f64; 3],


    // This member is not documented.
    #[allow(missing_docs)]
    pub torque: [f64; 3],

}



impl Default for DroneControl {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::DroneControl::default())
  }
}

impl rosidl_runtime_rs::Message for DroneControl {
  type RmwMsg = super::msg::rmw::DroneControl;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        force_des: msg.force_des,
        torque: msg.torque,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        force_des: msg.force_des,
        torque: msg.torque,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      force_des: msg.force_des,
      torque: msg.torque,
    }
  }
}


// Corresponds to quadrotor_msgs__msg__TrajectoryPoint

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct TrajectoryPoint {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub position: [f64; 3],


    // This member is not documented.
    #[allow(missing_docs)]
    pub velocity: [f64; 3],


    // This member is not documented.
    #[allow(missing_docs)]
    pub acceleration: [f64; 3],


    // This member is not documented.
    #[allow(missing_docs)]
    pub yaw: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub path_name: std::string::String,

}



impl Default for TrajectoryPoint {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::TrajectoryPoint::default())
  }
}

impl rosidl_runtime_rs::Message for TrajectoryPoint {
  type RmwMsg = super::msg::rmw::TrajectoryPoint;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        position: msg.position,
        velocity: msg.velocity,
        acceleration: msg.acceleration,
        yaw: msg.yaw,
        path_name: msg.path_name.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        position: msg.position,
        velocity: msg.velocity,
        acceleration: msg.acceleration,
      yaw: msg.yaw,
        path_name: msg.path_name.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      position: msg.position,
      velocity: msg.velocity,
      acceleration: msg.acceleration,
      yaw: msg.yaw,
      path_name: msg.path_name.to_string(),
    }
  }
}


