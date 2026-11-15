// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from car_msgs:msg/SensorCalibration.idl
// generated code does not contain a copyright notice

#include "car_msgs/msg/detail/sensor_calibration__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_car_msgs
const rosidl_type_hash_t *
car_msgs__msg__SensorCalibration__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xc3, 0x2c, 0x74, 0xd4, 0xd1, 0x24, 0x3f, 0x1a,
      0xdb, 0xb7, 0xda, 0x9a, 0xe6, 0x81, 0xd4, 0xc0,
      0xfc, 0x93, 0x8e, 0x48, 0xfb, 0xce, 0x55, 0x9c,
      0x2f, 0x06, 0xa0, 0x0d, 0xfd, 0xb0, 0x28, 0xba,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "std_msgs/msg/detail/header__functions.h"
#include "builtin_interfaces/msg/detail/time__functions.h"

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

static char car_msgs__msg__SensorCalibration__TYPE_NAME[] = "car_msgs/msg/SensorCalibration";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char std_msgs__msg__Header__TYPE_NAME[] = "std_msgs/msg/Header";

// Define type names, field names, and default values
static char car_msgs__msg__SensorCalibration__FIELD_NAME__header[] = "header";
static char car_msgs__msg__SensorCalibration__FIELD_NAME__is_calibrated[] = "is_calibrated";
static char car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_mean_accel_x[] = "mpu6050_mean_accel_x";
static char car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_mean_accel_y[] = "mpu6050_mean_accel_y";
static char car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_mean_accel_z[] = "mpu6050_mean_accel_z";
static char car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_var_accel_x[] = "mpu6050_var_accel_x";
static char car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_var_accel_y[] = "mpu6050_var_accel_y";
static char car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_var_accel_z[] = "mpu6050_var_accel_z";
static char car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_mean_gyro_x[] = "mpu6050_mean_gyro_x";
static char car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_mean_gyro_y[] = "mpu6050_mean_gyro_y";
static char car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_mean_gyro_z[] = "mpu6050_mean_gyro_z";
static char car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_var_gyro_x[] = "mpu6050_var_gyro_x";
static char car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_var_gyro_y[] = "mpu6050_var_gyro_y";
static char car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_var_gyro_z[] = "mpu6050_var_gyro_z";
static char car_msgs__msg__SensorCalibration__FIELD_NAME__cjmcu103_mean_angle[] = "cjmcu103_mean_angle";
static char car_msgs__msg__SensorCalibration__FIELD_NAME__cjmcu103_var_angle[] = "cjmcu103_var_angle";
static char car_msgs__msg__SensorCalibration__FIELD_NAME__cjmcu103_mean_anglespeed[] = "cjmcu103_mean_anglespeed";
static char car_msgs__msg__SensorCalibration__FIELD_NAME__cjmcu103_var_anglespeed[] = "cjmcu103_var_anglespeed";
static char car_msgs__msg__SensorCalibration__FIELD_NAME__wheelencoder_var_rotspeed[] = "wheelencoder_var_rotspeed";

static rosidl_runtime_c__type_description__Field car_msgs__msg__SensorCalibration__FIELDS[] = {
  {
    {car_msgs__msg__SensorCalibration__FIELD_NAME__header, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__SensorCalibration__FIELD_NAME__is_calibrated, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_mean_accel_x, 20, 20},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_mean_accel_y, 20, 20},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_mean_accel_z, 20, 20},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_var_accel_x, 19, 19},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_var_accel_y, 19, 19},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_var_accel_z, 19, 19},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_mean_gyro_x, 19, 19},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_mean_gyro_y, 19, 19},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_mean_gyro_z, 19, 19},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_var_gyro_x, 18, 18},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_var_gyro_y, 18, 18},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__SensorCalibration__FIELD_NAME__mpu6050_var_gyro_z, 18, 18},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__SensorCalibration__FIELD_NAME__cjmcu103_mean_angle, 19, 19},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__SensorCalibration__FIELD_NAME__cjmcu103_var_angle, 18, 18},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__SensorCalibration__FIELD_NAME__cjmcu103_mean_anglespeed, 24, 24},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__SensorCalibration__FIELD_NAME__cjmcu103_var_anglespeed, 23, 23},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {car_msgs__msg__SensorCalibration__FIELD_NAME__wheelencoder_var_rotspeed, 25, 25},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription car_msgs__msg__SensorCalibration__REFERENCED_TYPE_DESCRIPTIONS[] = {
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
car_msgs__msg__SensorCalibration__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {car_msgs__msg__SensorCalibration__TYPE_NAME, 30, 30},
      {car_msgs__msg__SensorCalibration__FIELDS, 19, 19},
    },
    {car_msgs__msg__SensorCalibration__REFERENCED_TYPE_DESCRIPTIONS, 2, 2},
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
  "bool is_calibrated\n"
  "float32 mpu6050_mean_accel_x\n"
  "float32 mpu6050_mean_accel_y\n"
  "float32 mpu6050_mean_accel_z\n"
  "float32 mpu6050_var_accel_x\n"
  "float32 mpu6050_var_accel_y\n"
  "float32 mpu6050_var_accel_z\n"
  "float32 mpu6050_mean_gyro_x\n"
  "float32 mpu6050_mean_gyro_y\n"
  "float32 mpu6050_mean_gyro_z\n"
  "float32 mpu6050_var_gyro_x\n"
  "float32 mpu6050_var_gyro_y\n"
  "float32 mpu6050_var_gyro_z\n"
  "float32 cjmcu103_mean_angle\n"
  "float32 cjmcu103_var_angle\n"
  "float32 cjmcu103_mean_anglespeed\n"
  "float32 cjmcu103_var_anglespeed\n"
  "float32 wheelencoder_var_rotspeed\n"
  "";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
car_msgs__msg__SensorCalibration__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {car_msgs__msg__SensorCalibration__TYPE_NAME, 30, 30},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 534, 534},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
car_msgs__msg__SensorCalibration__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[3];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 3, 3};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *car_msgs__msg__SensorCalibration__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *std_msgs__msg__Header__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
