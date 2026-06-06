/*
 * drive_control.hpp
 *
 *  Created on: Jun 5, 2026
 *      Author: valenstein
 */

#ifndef INC_DRIVE_CONTROL_HPP_
#define INC_DRIVE_CONTROL_HPP_

#include "stm32f4xx_hal.h"
#include "motor_control.hpp"
#include "sensor_collection.hpp"


class DriveControl: public MotorControl {
public:

	DriveControl(TIM_HandleTypeDef* handle, SensorCollection& sensorCollection);

	void controlSpeed();

private:

};



#endif /* INC_DRIVE_CONTROL_HPP_ */
