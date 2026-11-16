// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from car_msgs:msg/NodeState.idl
// generated code does not contain a copyright notice

#include "car_msgs/msg/detail/node_state__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_car_msgs
const rosidl_type_hash_t *
car_msgs__msg__NodeState__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xde, 0xdf, 0x72, 0x0b, 0x2b, 0xea, 0x58, 0x15,
      0xdb, 0x07, 0x17, 0x36, 0xf2, 0x6e, 0x4d, 0xbc,
      0x0d, 0x32, 0x1c, 0x67, 0x90, 0x85, 0x21, 0x86,
      0x02, 0xbf, 0x7a, 0x04, 0x92, 0xa7, 0x11, 0x92,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char car_msgs__msg__NodeState__TYPE_NAME[] = "car_msgs/msg/NodeState";

// Define type names, field names, and default values
static char car_msgs__msg__NodeState__FIELD_NAME__localizer_is_ready[] = "localizer_is_ready";

static rosidl_runtime_c__type_description__Field car_msgs__msg__NodeState__FIELDS[] = {
  {
    {car_msgs__msg__NodeState__FIELD_NAME__localizer_is_ready, 18, 18},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
car_msgs__msg__NodeState__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {car_msgs__msg__NodeState__TYPE_NAME, 22, 22},
      {car_msgs__msg__NodeState__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "bool localizer_is_ready";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
car_msgs__msg__NodeState__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {car_msgs__msg__NodeState__TYPE_NAME, 22, 22},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 23, 23},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
car_msgs__msg__NodeState__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *car_msgs__msg__NodeState__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
