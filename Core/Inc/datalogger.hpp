/*
 * datalogger.hpp
 *
 *  Created on: 16.03.2026
 *      Author: valen
 */

#ifndef INC_DATALOGGER_HPP_
#define INC_DATALOGGER_HPP_


#include <vector>
#include <cstdint>
#include "uart.hpp"

struct LogVariable {
	const char* varName;
	void* ptrVal;
	size_t size;
};


class DataLogger {
public:
	DataLogger(Uart& uart);
    void addVariable(const char* name, void* ptr, size_t size);
    void serialize(uint8_t* buffer);
    void log();

private:
    std::vector<LogVariable> m_variables;
    size_t m_totalSize;
    Uart& m_uart;
};


#endif /* INC_DATALOGGER_HPP_ */

