/*
 * main_app.cpp
 *
 *  Created on: 03.03.2026
 *      Author: valen
 */

#include "uart.hpp"

extern "C" {
    extern UART_HandleTypeDef huart2;
};

extern "C" void main_init()
{
	Uart uart_debug(&huart2);

};



