// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from quadrotor_msgs:msg/DroneState.idl
// generated code does not contain a copyright notice
#include "quadrotor_msgs/msg/detail/drone_state__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "quadrotor_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "quadrotor_msgs/msg/detail/drone_state__struct.h"
#include "quadrotor_msgs/msg/detail/drone_state__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "std_msgs/msg/detail/header__functions.h"  // header

// forward declare type support functions

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_quadrotor_msgs
bool cdr_serialize_std_msgs__msg__Header(
  const std_msgs__msg__Header * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_quadrotor_msgs
bool cdr_deserialize_std_msgs__msg__Header(
  eprosima::fastcdr::Cdr & cdr,
  std_msgs__msg__Header * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_quadrotor_msgs
size_t get_serialized_size_std_msgs__msg__Header(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_quadrotor_msgs
size_t max_serialized_size_std_msgs__msg__Header(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_quadrotor_msgs
bool cdr_serialize_key_std_msgs__msg__Header(
  const std_msgs__msg__Header * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_quadrotor_msgs
size_t get_serialized_size_key_std_msgs__msg__Header(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_quadrotor_msgs
size_t max_serialized_size_key_std_msgs__msg__Header(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_quadrotor_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, std_msgs, msg, Header)();


using _DroneState__ros_msg_type = quadrotor_msgs__msg__DroneState;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_quadrotor_msgs
bool cdr_serialize_quadrotor_msgs__msg__DroneState(
  const quadrotor_msgs__msg__DroneState * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: header
  {
    cdr_serialize_std_msgs__msg__Header(
      &ros_message->header, cdr);
  }

  // Field name: position
  {
    size_t size = 3;
    auto array_ptr = ros_message->position;
    cdr.serialize_array(array_ptr, size);
  }

  // Field name: velocity
  {
    size_t size = 3;
    auto array_ptr = ros_message->velocity;
    cdr.serialize_array(array_ptr, size);
  }

  // Field name: quaternion
  {
    size_t size = 4;
    auto array_ptr = ros_message->quaternion;
    cdr.serialize_array(array_ptr, size);
  }

  // Field name: omega
  {
    size_t size = 3;
    auto array_ptr = ros_message->omega;
    cdr.serialize_array(array_ptr, size);
  }

  // Field name: gyro_bias
  {
    size_t size = 3;
    auto array_ptr = ros_message->gyro_bias;
    cdr.serialize_array(array_ptr, size);
  }

  // Field name: accel_bias
  {
    size_t size = 3;
    auto array_ptr = ros_message->accel_bias;
    cdr.serialize_array(array_ptr, size);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_quadrotor_msgs
bool cdr_deserialize_quadrotor_msgs__msg__DroneState(
  eprosima::fastcdr::Cdr & cdr,
  quadrotor_msgs__msg__DroneState * ros_message)
{
  // Field name: header
  {
    cdr_deserialize_std_msgs__msg__Header(cdr, &ros_message->header);
  }

  // Field name: position
  {
    size_t size = 3;
    auto array_ptr = ros_message->position;
    cdr.deserialize_array(array_ptr, size);
  }

  // Field name: velocity
  {
    size_t size = 3;
    auto array_ptr = ros_message->velocity;
    cdr.deserialize_array(array_ptr, size);
  }

  // Field name: quaternion
  {
    size_t size = 4;
    auto array_ptr = ros_message->quaternion;
    cdr.deserialize_array(array_ptr, size);
  }

  // Field name: omega
  {
    size_t size = 3;
    auto array_ptr = ros_message->omega;
    cdr.deserialize_array(array_ptr, size);
  }

  // Field name: gyro_bias
  {
    size_t size = 3;
    auto array_ptr = ros_message->gyro_bias;
    cdr.deserialize_array(array_ptr, size);
  }

  // Field name: accel_bias
  {
    size_t size = 3;
    auto array_ptr = ros_message->accel_bias;
    cdr.deserialize_array(array_ptr, size);
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_quadrotor_msgs
size_t get_serialized_size_quadrotor_msgs__msg__DroneState(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _DroneState__ros_msg_type * ros_message = static_cast<const _DroneState__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: header
  current_alignment += get_serialized_size_std_msgs__msg__Header(
    &(ros_message->header), current_alignment);

  // Field name: position
  {
    size_t array_size = 3;
    auto array_ptr = ros_message->position;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: velocity
  {
    size_t array_size = 3;
    auto array_ptr = ros_message->velocity;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: quaternion
  {
    size_t array_size = 4;
    auto array_ptr = ros_message->quaternion;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: omega
  {
    size_t array_size = 3;
    auto array_ptr = ros_message->omega;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: gyro_bias
  {
    size_t array_size = 3;
    auto array_ptr = ros_message->gyro_bias;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: accel_bias
  {
    size_t array_size = 3;
    auto array_ptr = ros_message->accel_bias;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_quadrotor_msgs
size_t max_serialized_size_quadrotor_msgs__msg__DroneState(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Field name: header
  {
    size_t array_size = 1;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_std_msgs__msg__Header(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Field name: position
  {
    size_t array_size = 3;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: velocity
  {
    size_t array_size = 3;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: quaternion
  {
    size_t array_size = 4;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: omega
  {
    size_t array_size = 3;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: gyro_bias
  {
    size_t array_size = 3;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: accel_bias
  {
    size_t array_size = 3;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }


  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = quadrotor_msgs__msg__DroneState;
    is_plain =
      (
      offsetof(DataType, accel_bias) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_quadrotor_msgs
bool cdr_serialize_key_quadrotor_msgs__msg__DroneState(
  const quadrotor_msgs__msg__DroneState * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: header
  {
    cdr_serialize_key_std_msgs__msg__Header(
      &ros_message->header, cdr);
  }

  // Field name: position
  {
    size_t size = 3;
    auto array_ptr = ros_message->position;
    cdr.serialize_array(array_ptr, size);
  }

  // Field name: velocity
  {
    size_t size = 3;
    auto array_ptr = ros_message->velocity;
    cdr.serialize_array(array_ptr, size);
  }

  // Field name: quaternion
  {
    size_t size = 4;
    auto array_ptr = ros_message->quaternion;
    cdr.serialize_array(array_ptr, size);
  }

  // Field name: omega
  {
    size_t size = 3;
    auto array_ptr = ros_message->omega;
    cdr.serialize_array(array_ptr, size);
  }

  // Field name: gyro_bias
  {
    size_t size = 3;
    auto array_ptr = ros_message->gyro_bias;
    cdr.serialize_array(array_ptr, size);
  }

  // Field name: accel_bias
  {
    size_t size = 3;
    auto array_ptr = ros_message->accel_bias;
    cdr.serialize_array(array_ptr, size);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_quadrotor_msgs
size_t get_serialized_size_key_quadrotor_msgs__msg__DroneState(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _DroneState__ros_msg_type * ros_message = static_cast<const _DroneState__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: header
  current_alignment += get_serialized_size_key_std_msgs__msg__Header(
    &(ros_message->header), current_alignment);

  // Field name: position
  {
    size_t array_size = 3;
    auto array_ptr = ros_message->position;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: velocity
  {
    size_t array_size = 3;
    auto array_ptr = ros_message->velocity;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: quaternion
  {
    size_t array_size = 4;
    auto array_ptr = ros_message->quaternion;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: omega
  {
    size_t array_size = 3;
    auto array_ptr = ros_message->omega;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: gyro_bias
  {
    size_t array_size = 3;
    auto array_ptr = ros_message->gyro_bias;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: accel_bias
  {
    size_t array_size = 3;
    auto array_ptr = ros_message->accel_bias;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_quadrotor_msgs
size_t max_serialized_size_key_quadrotor_msgs__msg__DroneState(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;
  // Field name: header
  {
    size_t array_size = 1;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_key_std_msgs__msg__Header(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Field name: position
  {
    size_t array_size = 3;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: velocity
  {
    size_t array_size = 3;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: quaternion
  {
    size_t array_size = 4;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: omega
  {
    size_t array_size = 3;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: gyro_bias
  {
    size_t array_size = 3;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: accel_bias
  {
    size_t array_size = 3;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = quadrotor_msgs__msg__DroneState;
    is_plain =
      (
      offsetof(DataType, accel_bias) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _DroneState__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const quadrotor_msgs__msg__DroneState * ros_message = static_cast<const quadrotor_msgs__msg__DroneState *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_quadrotor_msgs__msg__DroneState(ros_message, cdr);
}

static bool _DroneState__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  quadrotor_msgs__msg__DroneState * ros_message = static_cast<quadrotor_msgs__msg__DroneState *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_quadrotor_msgs__msg__DroneState(cdr, ros_message);
}

static uint32_t _DroneState__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_quadrotor_msgs__msg__DroneState(
      untyped_ros_message, 0));
}

static size_t _DroneState__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_quadrotor_msgs__msg__DroneState(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_DroneState = {
  "quadrotor_msgs::msg",
  "DroneState",
  _DroneState__cdr_serialize,
  _DroneState__cdr_deserialize,
  _DroneState__get_serialized_size,
  _DroneState__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _DroneState__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_DroneState,
  get_message_typesupport_handle_function,
  &quadrotor_msgs__msg__DroneState__get_type_hash,
  &quadrotor_msgs__msg__DroneState__get_type_description,
  &quadrotor_msgs__msg__DroneState__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, quadrotor_msgs, msg, DroneState)() {
  return &_DroneState__type_support;
}

#if defined(__cplusplus)
}
#endif
