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
#include <car_msgs/msg/car_message.h>

extern UART_HandleTypeDef huart1;


rcl_allocator_t allocator;
rclc_support_t support;

rcl_node_t node;

rcl_publisher_t publisher;
rcl_subscription_t subscriber;

rclc_executor_t executor;

car_msgs__msg__CarMessage pub_msg;
std_msgs__msg__Int32 sub_msg;

bool cubemx_transport_open(struct uxrCustomTransport * transport);
bool cubemx_transport_close(struct uxrCustomTransport * transport);
size_t cubemx_transport_write(struct uxrCustomTransport* transport, const uint8_t * buf, size_t len, uint8_t * err);
size_t cubemx_transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err);


void init_mros() {
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
	    &publisher,
	    &node,
	    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
	    "/counter");
}

void mros_publish() {
    rcl_publish(&publisher, &pub_msg, NULL);
}

