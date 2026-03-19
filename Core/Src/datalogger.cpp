/*
 * datalogger.cpp
 *
 *  Created on: 16.03.2026
 *      Author: valen
 */

#include "datalogger.hpp"
#include <cstring>

DataLogger::DataLogger(Uart& uart): m_uart{uart} {
	m_totalSize = 0;
}


void DataLogger::addVariable(const char* name, void* ptr, size_t size) {
	m_variables.push_back({name, ptr, size});
	m_totalSize += size;
}

void DataLogger::serialize(uint8_t* buffer) {
    size_t offset = 0;
    for (auto& var : m_variables) {
        memcpy(buffer + offset, var.ptrVal, var.size);
        offset += var.size;
    }
}

void DataLogger::log() {
    uint8_t buffer[m_totalSize];
    serialize(buffer);
    m_uart.send(buffer, m_totalSize);
}

/*
 * es fehlen noch header und footer files um korrekt decodieren zu können!!
 */
