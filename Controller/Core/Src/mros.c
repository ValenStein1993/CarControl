/*
 * mros.c
 *
 *  Created on: 17.07.2026
 *      Author: valen
 */

#include "stm32f4xx_hal.h"
#include <string.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <uxr/client/transport.h>
#include <rmw_microxrcedds_c/config.h>
#include <rmw_microros/rmw_microros.h>

#include <std_msgs/msg/int32.h>
#include <std_msgs/msg/float32.h>
#include <car_msgs/msg/sensor_measurements.h>
#include <car_msgs/msg/sensor_calibration.h>

extern UART_HandleTypeDef huart1;


rcl_allocator_t allocator;
rclc_support_t support;

rcl_node_t node;

rcl_publisher_t pub_snsr_meas, pub_snsr_cal;
rcl_subscription_t subscriber;

rclc_executor_t executor;

car_msgs__msg__SensorMeasurements pub_msg_meas;
car_msgs__msg__SensorCalibration pub_msg_cal;

std_msgs__msg__Int32 sub_msg;

bool cubemx_transport_open(struct uxrCustomTransport * transport);
bool cubemx_transport_close(struct uxrCustomTransport * transport);
size_t cubemx_transport_write(struct uxrCustomTransport* transport, const uint8_t * buf, size_t len, uint8_t * err);
size_t cubemx_transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err);


void mros_init() {
	rmw_uros_set_custom_transport(
		true,
		(void *)&huart1,
		cubemx_transport_open,
		cubemx_transport_close,
		cubemx_transport_write,
		cubemx_transport_read
	);

	rmw_ret_t ret;
	do {
		ret = rmw_uros_ping_agent(100, 1);   // 100ms timeout per attempt
	} while (ret != RMW_RET_OK);

	allocator = rcl_get_default_allocator();
	rclc_support_init(&support, 0, NULL, &allocator);
	rclc_node_init_default(&node, "car_controller", "", &support);

	rclc_publisher_init_default(
	    &pub_snsr_meas,
	    &node,
	    ROSIDL_GET_MSG_TYPE_SUPPORT(car_msgs, msg, SensorMeasurements),
	    "/sensor/measurement");

	rclc_publisher_init_default(
		&pub_snsr_cal,
		&node,
		ROSIDL_GET_MSG_TYPE_SUPPORT(car_msgs, msg, SensorCalibration),
		"/sensor/calibration");
}

void mros_publish_sensor_meas() {
    rcl_publish(&pub_snsr_meas, &pub_msg_meas, NULL);
}

void mros_publish_sensor_cal() {
    rcl_publish(&pub_snsr_cal, &pub_msg_cal, NULL);
}

