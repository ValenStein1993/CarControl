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
#include "simulator.hpp"

class SteerControlAktr: public MotorControl {
public:

	SteerControlAktr(TIM_HandleTypeDef* handle, SensorCollection& sensorCollection);

	void steerLeft();
	void steerRight();
	void setAngle(float target);
	void controlAngle();

private:

};

class SteerControlSim: public SteerControlAktr {
public:

	SteerControlSim(TIM_HandleTypeDef* handle, SensorCollection& sensorCollection)
		: SteerControlAktr{handle, sensorCollection} {};

	void setAngle(float target) {
		sim->SetAngle = target;
	};

};

#ifdef SIMULATION
using SteerControl = SteerControlSim;
#else
using SteerControl = SteerControlAktr;
#endif


#endif /* INC_STEER_CONTROL_HPP_ */
