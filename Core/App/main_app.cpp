/*
 * main_app.cpp
 *
 *  Created on: 03.03.2026
 *      Author: valen
 */

#include "main_app.hpp"
#include "uart.hpp"
#include "scheduler.hpp"

extern "C" {
    extern UART_HandleTypeDef huart2;
    extern TIM_HandleTypeDef htim3;
};

// initialize uart object
static 	Uart uart_debug(&huart2);
// initialize task scheduler
static Scheduler scheduler;

void main_init()
{
	// setup interrupts on overflow for timer3
	HAL_TIM_Base_Start_IT(&htim3);

};

void main_loop()
{
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
		uart_debug.print("TEST");
	}
};

extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
        scheduler.update();
    }
}




