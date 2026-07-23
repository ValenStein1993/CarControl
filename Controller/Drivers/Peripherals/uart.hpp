/*
 * uart.h
 *
 *  Created on: 01.03.2026
 *      Author: valen
 */

#ifndef UART_HPP_
#define UART_HPP_

#include "stm32f4xx_hal.h"

class Uart
{
public:
    Uart(UART_HandleTypeDef* handle);

    void print(const char* str);
    void send(uint8_t* buffer, size_t& size);

private:
    UART_HandleTypeDef* m_handle;
};


#endif /* UART_H_ */
