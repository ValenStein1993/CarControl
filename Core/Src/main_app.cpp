/*
 * main_app.cpp
 *
 *  Created on: 03.03.2026
 *      Author: valen
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

extern "C" {
    extern UART_HandleTypeDef huart2;
    extern TIM_HandleTypeDef htim2;
    extern TIM_HandleTypeDef htim3;
    extern TIM_HandleTypeDef htim10;
    extern I2C_HandleTypeDef hi2c1;
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
//static MPU6050 mpu6050(&hi2c1);
// initialize wheel encoder
//static WheelEncoder wheelEncoder(&htim2);
// initialize localizer
//static Localizer localizer(mpu6050, wheelEncoder);
// initialize logger
static DataLogger datalogger{uart};
// initialize power sensing
static INA219 powerSensor(&hi2c1);

float curr;


void main_init() {
	// setup interrupts on overflow of timer3
	HAL_TIM_Base_Start_IT(&htim3);
	// set initial duty cycle
	HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
	driveControl.setDutyCycle(0.9);

	// add logger variables
	datalogger.addVariable<uint8_t>("10ms", &scheduler.tick100ms);
	datalogger.addVariable<uint8_t>("sum1000", &scheduler.sum1000);
	datalogger.addVariable<float>("current", &curr);


};

void main_loop() {
	if (scheduler.run10ms()) {
		curr = powerSensor.readCurrent();
	}

	if (scheduler.run100ms()) {
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




