/*
 * main_app.cpp
 *
 *  Created on: 03.03.2026
 *      Author: valen
 */



/*
 *
 * PID Controller für Motoren
 * Kalibrierung von Odometrie für x richtung (gerade aus)
 *
 */

#include "main_app.hpp"
#include "uart.hpp"
#include "scheduler.hpp"
#include "motor_control.hpp"
#include "mpu6050.hpp"
#include "wheel_encoder.hpp"
#include "datatypes.hpp"
#include "datalogger.hpp"
#include "localizer.hpp"
#include "ina219.hpp"
#include "steer_control.hpp"
#include "cjmcu103.hpp"

extern "C" {
    extern UART_HandleTypeDef huart2;
    extern TIM_HandleTypeDef htim2;
    extern TIM_HandleTypeDef htim3;
    extern TIM_HandleTypeDef htim10;
    extern TIM_HandleTypeDef htim12;
    extern I2C_HandleTypeDef hi2c1;
    extern ADC_HandleTypeDef hadc1;
};

// global task time
float dt = 0;
// initialize uart object
static 	Uart uart(&huart2);
// initialize task scheduler
static Scheduler scheduler;
// initialize drive motor control
static MotorControl driveControl(&htim10);
// initialize accelerometer and gyroscope
static MPU6050 accelerometer(&hi2c1);
// initialize wheel encoder
static WheelEncoder wheelEncoder(&htim2);
// initialize localizer
//static Localizer localizer(mpu6050, wheelEncoder);
// initialize logger
static DataLogger datalogger{uart};
// initialize power sensing
static INA219 powerSensor(&hi2c1);
// initialize power sensing
static CJMCU103 angleSensor(&hadc1);
// initialize steering control
static SteerControl steerControl(&htim12, powerSensor, angleSensor);
// define logging variables
float curr, angle, angleSpeed;


void main_init() {
	// setup interrupts on overflow of timer3
	HAL_TIM_Base_Start_IT(&htim3);
	// set initial duty cycle
	HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);

	// driveControl.setDutyCycle(0.9);

	// since constructors of static objects are called before main() and HAL_init,
	// calibration and initialization of sensors have to be executed from separate functions

	accelerometer.init();
	powerSensor.init();
	angleSensor.init();

	// add logger variables
	datalogger.addVariable<float>("current", &curr);
	datalogger.addVariable<float>("angle", &angle);
	datalogger.addVariable<float>("angleSpeed", &angleSpeed);
};

void main_loop() {
	if (scheduler.run10ms()) {
	}

	if (scheduler.run100ms()) {
		steerControl.calibrate();

		curr = powerSensor.readPower();
		angle = angleSensor.readAngle();
		angleSpeed = angleSensor.readAngleSpeed();
		datalogger.log();
	}

	if (scheduler.run1000ms()) {
		datalogger.sendConfig();
		//localizer.update();
	}
};

extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM3)
    {
        scheduler.update();
    }
}




