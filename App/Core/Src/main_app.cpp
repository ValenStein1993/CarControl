/*
 * main_app.cpp
 *
 *  Created on: 03.03.2026
 *      Author: valen
 */



/*
 *
 * PID Bedatung festlegen!
 * Encoder Berechnung auf interrupts außerhalb der main loop umstellen
 *
 */
#include <cstdint>
#include "cmsis_os2.h"

#include "main_app.hpp"
#include "uart.hpp"
#include "drive_control.hpp"
#include "mpu6050.hpp"
#include "wheel_encoder.hpp"
#include "datatypes.hpp"
#include "datalogger.hpp"
#include "localizer.hpp"
#include "ina219.hpp"
#include "steer_control.hpp"
#include "cjmcu103.hpp"
#include "sensor_collection.hpp"
#include "sensor_handler.hpp"
#include "logging_vars.hpp"


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

AppState appState = AppState::INIT;

Uart uart(&huart2);
DataLogger datalogger{uart};

// initialize sensors
MPU6050 accelerometer(&hi2c1);
WheelEncoder wheelEncoder(&htim2);
INA219 powerSensor(&hi2c1);
CJMCU103 angleSensor(&hadc1);
SensorCollection sensorCollection{accelerometer, wheelEncoder, powerSensor, angleSensor};
SensorHandler sensorHandler(sensorCollection);

// initialize controllers
DriveControl driveControl(&htim10, sensorCollection);
SteerControl steerControl(&htim12, sensorCollection);
Localizer localizer(sensorCollection);

void main_init() {
	// setup interrupts on overflow of timer3
	HAL_TIM_Base_Start_IT(&htim3);
	// set initial duty cycle
	HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);

	appState = AppState::INIT;
	datalogger.registerLogVariables(logVars);
	sensorHandler.initSensors();
	localizer.initStateSpace();

}

uint32_t setCycleTime(uint32_t lastTime) {
	uint32_t currentTime = osKernelGetTickCount();
	uint32_t tickFreq = osKernelGetTickFreq();

	dt = ((currentTime - lastTime) * 1000) / tickFreq;
	return currentTime;
}

void RunControlTask_(void *argument) {
	static uint32_t lastTime = 0;
	lastTime = setCycleTime(lastTime);

	switch (appState) {
		case AppState::RUNNING:
			driveControl.setSpeed(0.5);
			steerControl.setAngle(20);

			driveControl.controlSpeed();
			steerControl.controlAngle();

			localizer.updateStateSpace();
			break;
		case AppState::ERROR:
			break;
	}
}

void RunSensorTask_(void *argument) {
	static uint32_t lastTime = 0;

	sensorHandler.updateSensorValues();
	switch (appState) {
		case AppState::INIT:
			appState = AppState::CALIBRATION;
		case AppState::CALIBRATION: {
			bool sensorsReady = sensorHandler.calibrateSensors(driveControl, steerControl);
			if (sensorsReady) {
				appState = AppState::RUNNING;
			}
			break;
		}
		case AppState::RUNNING:
			break;
		case AppState::ERROR:
			break;
	}
}

void RunStatusTask_(void *argument) {
	datalogger.log();
	datalogger.sendConfig();

}

void RunMicroROSTask_(void *argument) {
	
}




