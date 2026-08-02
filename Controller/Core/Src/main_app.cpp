/*
 * main_app.cpp
 *
 *  Created on: 03.03.2026
 *      Author: valen
 */



/*
 *
 * PID Bedatung festlegen!
 *
 */

#include <cstdint>
#include "stm32f4xx_hal.h"
#include "cmsis_os2.h"

#include "main_app.hpp"
#include "uart.hpp"
#include "drive_control.hpp"
#include "mpu6050.hpp"
#include "wheel_encoder.hpp"
#include "datatypes.hpp"
#include "datalogger.hpp"
#include "ina219.hpp"
#include "steer_control.hpp"
#include "cjmcu103.hpp"
#include "sensor_handler.hpp"
#include "mros.h"
#include <car_msgs/msg/sensor_measurements.h>
#include <car_msgs/msg/sensor_calibration.h>



extern "C" {
    extern UART_HandleTypeDef huart2;
    extern TIM_HandleTypeDef htim2;
    extern TIM_HandleTypeDef htim3;
    extern TIM_HandleTypeDef htim10;
    extern TIM_HandleTypeDef htim12;
    extern I2C_HandleTypeDef hi2c1;
    extern ADC_HandleTypeDef hadc1;
    extern car_msgs__msg__SensorMeasurements pub_msg_meas;
    extern car_msgs__msg__SensorCalibration pub_msg_cal;

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

// initialize sensor handler
SensorHandler sensorHandler(
	accelerometer,
	wheelEncoder,
	powerSensor,
	angleSensor
);

// initialize controllers
DriveControl driveControl(&htim10, sensorHandler.sensorVars_);
SteerControl steerControl(&htim12, sensorHandler.sensorVars_);



void main_init() {
	// setup interrupts on overflow of timer3
	HAL_TIM_Base_Start_IT(&htim3);
	// set initial duty cycle
	HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);

	// add logging variables
	datalogger.addVariable<float>("angle", &sensorHandler.sensorVars_.angle.val);
	datalogger.addVariable<float>("angleSpeed", &sensorHandler.sensorVars_.angleSpeed.val);
	datalogger.addVariable<float>("translSpeed", &sensorHandler.sensorVars_.translSpeed.val);
	datalogger.addVariable<float>("accelX", &sensorHandler.sensorVars_.accel.val.x);
	datalogger.addVariable<float>("accelY", &sensorHandler.sensorVars_.accel.val.y);
	datalogger.addVariable<float>("accelZ", &sensorHandler.sensorVars_.accel.val.z);
	datalogger.addVariable<bool>("accelIsReady", &accelerometer.isReady_);
	datalogger.addVariable<bool>("wheelEncoderIsReady", &wheelEncoder.isReady_);
	datalogger.addVariable<bool>("angleSensorIsReady", &angleSensor.isReady_);

	appState = AppState::INIT;
	sensorHandler.initSensors();
}

void updateControllerMessage() {
	pub_msg_meas.mpu6050_accel_x = sensorHandler.sensorVars_.accel.val.x;
	pub_msg_meas.mpu6050_accel_y = sensorHandler.sensorVars_.accel.val.y;
	pub_msg_meas.mpu6050_accel_z = sensorHandler.sensorVars_.accel.val.z;
	pub_msg_meas.mpu6050_gyro_x = sensorHandler.sensorVars_.gyro.val.x;
	pub_msg_meas.mpu6050_gyro_y = sensorHandler.sensorVars_.gyro.val.y;
	pub_msg_meas.mpu6050_gyro_z = sensorHandler.sensorVars_.gyro.val.z;
	pub_msg_meas.ina219_current = sensorHandler.sensorVars_.current.val;
	pub_msg_meas.ina219_power = sensorHandler.sensorVars_.power.val;
	pub_msg_meas.cjmcu103_angle = sensorHandler.sensorVars_.angle.val;
	pub_msg_meas.cjmcu103_anglespeed = sensorHandler.sensorVars_.angleSpeed.val;
	pub_msg_meas.wheelencoder_rotspeed = sensorHandler.sensorVars_.rotSpeed.val;
	pub_msg_meas.wheelencoder_translspeed = sensorHandler.sensorVars_.translSpeed.val;

	pub_msg_cal.mpu6050_mean_accel_x = sensorHandler.sensorVars_.accel.mean.x;
	pub_msg_cal.mpu6050_mean_accel_y = sensorHandler.sensorVars_.accel.mean.y;
	pub_msg_cal.mpu6050_mean_accel_z = sensorHandler.sensorVars_.accel.mean.z;
	pub_msg_cal.mpu6050_var_accel_x = sensorHandler.sensorVars_.accel.var.x;
	pub_msg_cal.mpu6050_var_accel_y = sensorHandler.sensorVars_.accel.var.y;
	pub_msg_cal.mpu6050_var_accel_z = sensorHandler.sensorVars_.accel.var.z;
	pub_msg_cal.mpu6050_mean_gyro_x = sensorHandler.sensorVars_.gyro.mean.x;
	pub_msg_cal.mpu6050_mean_gyro_y = sensorHandler.sensorVars_.gyro.mean.y;
	pub_msg_cal.mpu6050_mean_gyro_z = sensorHandler.sensorVars_.gyro.mean.z;
	pub_msg_cal.mpu6050_var_gyro_x = sensorHandler.sensorVars_.gyro.var.x;
	pub_msg_cal.mpu6050_var_gyro_y = sensorHandler.sensorVars_.gyro.var.y;
	pub_msg_cal.mpu6050_var_gyro_z = sensorHandler.sensorVars_.gyro.var.z;
	pub_msg_cal.cjmcu103_mean_angle = sensorHandler.sensorVars_.angle.mean;
	pub_msg_cal.cjmcu103_var_angle = sensorHandler.sensorVars_.angle.var;
	pub_msg_cal.cjmcu103_mean_anglespeed = sensorHandler.sensorVars_.angleSpeed.mean;
	pub_msg_cal.cjmcu103_var_anglespeed = sensorHandler.sensorVars_.angleSpeed.var;
	pub_msg_cal.wheelencoder_var_rotspeed = sensorHandler.sensorVars_.rotSpeed.var;
}

void runPeriodicTask(void (*task_fn)(void *), void *arg, uint32_t period_ms) {
    uint32_t tickFreq = osKernelGetTickFreq();
    uint32_t periodTicks = (tickFreq * period_ms) / 1000u;
    uint32_t nextWake = osKernelGetTickCount();

    for (;;) {
		dt = (float)period_ms / 1000.0f;
        task_fn(arg);

        nextWake += periodTicks;
        int32_t delayTicks = (int32_t)(nextWake - osKernelGetTickCount());
        if (delayTicks > 0) {
            osDelay(delayTicks);
        } else {
            nextWake = osKernelGetTickCount();
        }
    }
}

void controlTask(void *argument) {
	switch (appState) {
		case AppState::RUNNING:
			driveControl.setSpeed(0.5);
			steerControl.setAngle(20);

			driveControl.controlSpeed();
			steerControl.controlAngle();

			break;
		case AppState::ERROR:
			break;
	}
}

void sensorTask(void *argument) {
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

void statusTask(void *argument) {
	datalogger.log();
	datalogger.sendConfig();

}

void microROSTask(void *argument) {
	static int cnt = 0;

	updateControllerMessage();
	mros_publish_sensor_meas();

	if (++cnt >= 10) {
		cnt = 0;
		mros_publish_sensor_cal();
	}
}




