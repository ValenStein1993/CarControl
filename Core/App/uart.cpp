#include <uart.hpp>
#include <cstring>

Uart::Uart(UART_HandleTypeDef* handle)
{
	m_handle = handle;
}

void Uart::print(const char* str)
{
    HAL_UART_Transmit(
        m_handle,
        (uint8_t*)str,
        strlen(str),
        HAL_MAX_DELAY
    );
}
