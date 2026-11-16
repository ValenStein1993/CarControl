// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from car_msgs:msg/DebugController.idl
// generated code does not contain a copyright notice

#include "car_msgs/msg/detail/debug_controller__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_car_msgs
const rosidl_type_hash_t *
car_msgs__msg__DebugController__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xdd, 0x50, 0xe6, 0xbe, 0x26, 0xe5, 0x10, 0xb0,
      0x4b, 0x0c, 0x71, 0x94, 0x14, 0x1b, 0x7f, 0x40,
      0x91, 0x5d, 0x06, 0x6c, 0x8b, 0x76, 0xa1, 0xe2,
      0x9e, 0x23, 0x8f, 0xaf, 0x9e, 0x25, 0xcb, 0x4a,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "std_msgs/msg/detail/header__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t std_msgs__msg__Header__EXPECTED_HASH = {1, {
    0xf4, 0x9f, 0xb3, 0xae, 0x2c, 0xf0, 0x70, 0xf7,
    0x93, 0x64, 0x5f, 0xf7, 0x49, 0x68, 0x3a, 0xc6,
    0xb0, 0x62, 0x03, 0xe4, 0x1c, 0x89, 0x1e, 0x17,
    0x70, 0x1b, 0x1c, 0xb5, 0x97, 0xce, 0x6a, 0x01,
  }};
#endif

static char car_msgs__msg__DebugController__TYPE_NAME[] = "car_msgs/msg/DebugController";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char std_msgs__msg__Header__TYPE_NAME[] = "std_msgs/msg/Header";

// Define type names, field names, and default values
static char car_msgs__msg__DebugController__FIELD_NAME__header[] = "header";
static char car_msgs__msg__DebugController__FIELD_NAME__yaw_rate[] = "yaw_rate";
static char car_msgs__msg__DebugController__FIELD_NAME__yaw[] = "yaw";
static char car_msgs__msg__DebugController__FIELD_NAME__cn_yaw[] = "cn_yaw";
static char car_msgs__msg__DebugController__FIELD_NAME__speed[] = "speed";
static char car_msgs__msg__DebugController__FIELD_NAME__steering_angle[] = "steering_angle";
static char car_msgs__msg__DebugController__FIELD_NAME__idx_closest_node[] = "idx_closest_node";
static char car_msgs__msg__DebugController__FIELD_NAME__cte[] = "cte";
static char car_msgs__msg__DebugController__FIELD_NAME__heading_error[] = "heading_error";

static rosidl_runtime_c__type_description__Field car_msgs__msg__DebugController__FIELDS[] = {
  {
    {car_msgs__msg__DebugController__FIELD_NAME__header, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__DebugController__FIELD_NAME__yaw_rate, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__DebugController__FIELD_NAME__yaw, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__DebugController__FIELD_NAME__cn_yaw, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__DebugController__FIELD_NAME__speed, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__DebugController__FIELD_NAME__steering_angle, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__DebugController__FIELD_NAME__idx_closest_node, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__DebugController__FIELD_NAME__cte, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__DebugController__FIELD_NAME__heading_error, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription car_msgs__msg__DebugController__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
car_msgs__msg__DebugController__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {car_msgs__msg__DebugController__TYPE_NAME, 28, 28},
      {car_msgs__msg__DebugController__FIELDS, 9, 9},
    },
    {car_msgs__msg__DebugController__REFERENCED_TYPE_DESCRIPTIONS, 2, 2},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&std_msgs__msg__Header__EXPECTED_HASH, std_msgs__msg__Header__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = std_msgs__msg__Header__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "std_msgs/Header header\n"
  "\n"
  "float32 yaw_rate\n"
  "float32 yaw\n"
  "float32 cn_yaw\n"
  "float32 speed\n"
  "float32 steering_angle \n"
  "int32 idx_closest_node\n"
  "float32 cte\n"
  "float32 heading_error";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
car_msgs__msg__DebugController__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {car_msgs__msg__DebugController__TYPE_NAME, 28, 28},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 162, 162},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
car_msgs__msg__DebugController__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[3];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 3, 3};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *car_msgs__msg__DebugController__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *std_msgs__msg__Header__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
