/*
 * motor_control.hpp
 *
 *  Created on: 08.03.2026
 *      Author: valen
 */

#ifndef INC_STEER_CONTROL_HPP_
#define INC_STEER_CONTROL_HPP_

#include "datatypes.hpp"
#include "stm32f4xx_hal.h"
#include "motor_control.hpp"
#include "sensor_collection.hpp"

class SteerControl: public MotorControl {
public:

	SteerControl(TIM_HandleTypeDef* handle, SensorCollection& sensorCollection);

	void steerLeft();
	void steerRight();
	void controlAngle();

private:

};


#endif /* INC_STEER_CONTROL_HPP_ */
