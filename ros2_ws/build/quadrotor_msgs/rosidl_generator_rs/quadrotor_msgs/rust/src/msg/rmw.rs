#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "quadrotor_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__quadrotor_msgs__msg__DroneState() -> *const std::ffi::c_void;
}

#[link(name = "quadrotor_msgs__rosidl_generator_c")]
extern "C" {
    fn quadrotor_msgs__msg__DroneState__init(msg: *mut DroneState) -> bool;
    fn quadrotor_msgs__msg__DroneState__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DroneState>, size: usize) -> bool;
    fn quadrotor_msgs__msg__DroneState__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DroneState>);
    fn quadrotor_msgs__msg__DroneState__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DroneState>, out_seq: *mut rosidl_runtime_rs::Sequence<DroneState>) -> bool;
}

// Corresponds to quadrotor_msgs__msg__DroneState
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DroneState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !quadrotor_msgs__msg__DroneState__init(&mut msg as *mut _) {
        panic!("Call to quadrotor_msgs__msg__DroneState__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DroneState {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { quadrotor_msgs__msg__DroneState__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { quadrotor_msgs__msg__DroneState__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { quadrotor_msgs__msg__DroneState__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DroneState {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DroneState where Self: Sized {
  const TYPE_NAME: &'static str = "quadrotor_msgs/msg/DroneState";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__quadrotor_msgs__msg__DroneState() }
  }
}


#[link(name = "quadrotor_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__quadrotor_msgs__msg__DroneControl() -> *const std::ffi::c_void;
}

#[link(name = "quadrotor_msgs__rosidl_generator_c")]
extern "C" {
    fn quadrotor_msgs__msg__DroneControl__init(msg: *mut DroneControl) -> bool;
    fn quadrotor_msgs__msg__DroneControl__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DroneControl>, size: usize) -> bool;
    fn quadrotor_msgs__msg__DroneControl__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DroneControl>);
    fn quadrotor_msgs__msg__DroneControl__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DroneControl>, out_seq: *mut rosidl_runtime_rs::Sequence<DroneControl>) -> bool;
}

// Corresponds to quadrotor_msgs__msg__DroneControl
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DroneControl {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub force_des: [f64; 3],


    // This member is not documented.
    #[allow(missing_docs)]
    pub torque: [f64; 3],

}



impl Default for DroneControl {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !quadrotor_msgs__msg__DroneControl__init(&mut msg as *mut _) {
        panic!("Call to quadrotor_msgs__msg__DroneControl__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DroneControl {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { quadrotor_msgs__msg__DroneControl__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { quadrotor_msgs__msg__DroneControl__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { quadrotor_msgs__msg__DroneControl__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DroneControl {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DroneControl where Self: Sized {
  const TYPE_NAME: &'static str = "quadrotor_msgs/msg/DroneControl";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__quadrotor_msgs__msg__DroneControl() }
  }
}


#[link(name = "quadrotor_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__quadrotor_msgs__msg__TrajectoryPoint() -> *const std::ffi::c_void;
}

#[link(name = "quadrotor_msgs__rosidl_generator_c")]
extern "C" {
    fn quadrotor_msgs__msg__TrajectoryPoint__init(msg: *mut TrajectoryPoint) -> bool;
    fn quadrotor_msgs__msg__TrajectoryPoint__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<TrajectoryPoint>, size: usize) -> bool;
    fn quadrotor_msgs__msg__TrajectoryPoint__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<TrajectoryPoint>);
    fn quadrotor_msgs__msg__TrajectoryPoint__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<TrajectoryPoint>, out_seq: *mut rosidl_runtime_rs::Sequence<TrajectoryPoint>) -> bool;
}

// Corresponds to quadrotor_msgs__msg__TrajectoryPoint
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct TrajectoryPoint {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


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
    pub path_name: rosidl_runtime_rs::String,

}



impl Default for TrajectoryPoint {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !quadrotor_msgs__msg__TrajectoryPoint__init(&mut msg as *mut _) {
        panic!("Call to quadrotor_msgs__msg__TrajectoryPoint__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for TrajectoryPoint {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { quadrotor_msgs__msg__TrajectoryPoint__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { quadrotor_msgs__msg__TrajectoryPoint__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { quadrotor_msgs__msg__TrajectoryPoint__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for TrajectoryPoint {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for TrajectoryPoint where Self: Sized {
  const TYPE_NAME: &'static str = "quadrotor_msgs/msg/TrajectoryPoint";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__quadrotor_msgs__msg__TrajectoryPoint() }
  }
}


