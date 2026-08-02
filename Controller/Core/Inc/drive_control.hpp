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
#include "datatypes.hpp"
#include "simulator.hpp"



class DriveControlActr: public MotorControl {
public:

	DriveControlActr(TIM_HandleTypeDef* handle, SensorVars& sensorVars);

	void setSpeed(float target);
	void controlSpeed();

private:

};

class DriveControlSim: public DriveControlActr {
public:

	DriveControlSim(TIM_HandleTypeDef* handle, SensorVars& sensorVars)
		: DriveControlActr{handle, sensorVars} {};

	void setSpeed(float target) {
		sim->SetSpeed = target;
	};

};

#ifdef SIMULATION
using DriveControl = DriveControlSim;
#else
using DriveControl = DriveControlActr;
#endif

#endif /* INC_DRIVE_CONTROL_HPP_ */
