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
#include "simulator.hpp"



class DriveControlAktr: public MotorControl {
public:

	DriveControlAktr(TIM_HandleTypeDef* handle, SensorCollection& sensorCollection);

	void setSpeed(float target);
	void controlSpeed();

private:

};

class DriveControlSim: public DriveControlAktr {
public:

	DriveControlSim(TIM_HandleTypeDef* handle, SensorCollection& sensorCollection)
		: DriveControlAktr{handle, sensorCollection} {};

	void setSpeed(float target) {
		sim->SetSpeed = target;
	};

};

#ifdef SIMULATION
using DriveControl = DriveControlSim;
#else
using DriveControl = DriveControlAktr;
#endif

#endif /* INC_DRIVE_CONTROL_HPP_ */
