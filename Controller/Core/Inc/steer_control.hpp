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
#include "simulator.hpp"

class SteerControlActr: public MotorControl {
public:

	SteerControlActr(TIM_HandleTypeDef* handle, SensorVars& sensorVars);

	void steerLeft();
	void steerRight();
	void setAngle(float target);
	void controlAngle();

private:

};

class SteerControlSim: public SteerControlActr {
public:

	SteerControlSim(TIM_HandleTypeDef* handle, SensorVars& sensorVars)
		: SteerControlActr{handle, sensorVars} {};

	void setAngle(float target) {
		sim->SetAngle = target;
	};

};

#ifdef SIMULATION
using SteerControl = SteerControlSim;
#else
using SteerControl = SteerControlActr;
#endif


#endif /* INC_STEER_CONTROL_HPP_ */
