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

extern "C" {
    extern UART_HandleTypeDef huart2;
    extern TIM_HandleTypeDef htim2;
    extern TIM_HandleTypeDef htim3;
    extern TIM_HandleTypeDef htim10;
    extern I2C_HandleTypeDef hi2c1;
};

// initialize uart object
static 	Uart uartDebug(&huart2);
// initialize task scheduler
static Scheduler scheduler;
// initialize drive motor control
static MotorControl driveControl(&htim10);
// initialize accelerometer and gyroscope
static MPU6050 mpu6050(&hi2c1);
// initialize wheel encoder
static WheelEncoder wheelEncoder(&htim2);


void main_init() {
	// setup interrupts on overflow of timer3
	HAL_TIM_Base_Start_IT(&htim3);
	// set initial duty cycle
	driveControl.setDutyCycle(0.9);

};

void main_loop() {
	if (scheduler.tick10ms)
	{
		scheduler.tick10ms--;

	}

	if (scheduler.tick100ms)
	{
		scheduler.tick100ms--;

	}

	if (scheduler.tick1000ms)
	{
		scheduler.tick1000ms--;
		uartDebug.print("TEST");
		wheelEncoder.calcRotSpeed(1);
	}
};

extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM3)
    {
        scheduler.update();
    }
}




