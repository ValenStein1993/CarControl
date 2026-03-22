/*
 * datalogger.cpp
 *
 *  Created on: 16.03.2026
 *      Author: valen
 */

#include "datalogger.hpp"
#include <cstring>

DataLogger::DataLogger(Uart& uart): m_uart{uart} {}

void DataLogger::serialize(uint8_t* buffer, size_t& size) {
    size_t offset = 0;
    for (auto& var : m_variables) {
        memcpy(buffer + offset, var.ptrVal, var.size);
        offset += var.size;
    }
    size = offset;
}

void DataLogger::log() {
    uint8_t buffer[128];
    size_t size = 0;
    serialize(buffer + 3, size);
    buffer[0] = 0xAA;
    buffer[1] = 0x55;
    buffer[2] = 0x02;
    m_uart.send(buffer, size);
}

void DataLogger::sendConfig() {
    uint8_t buffer[128];
    size_t offset = 0;

    buffer[offset++] = 0xAA;
    buffer[offset++] = 0x55;
    buffer[offset++] = 0x01;

    size_t len_index = offset++;

    for (auto& var : m_variables) {
        uint8_t name_len = strlen(var.varName);

        buffer[offset++] = name_len;

        memcpy(buffer + offset, var.varName, name_len);
        offset += name_len;

        buffer[offset++] = static_cast<uint8_t>(var.varType);
        buffer[offset++] = var.size;
    }

    buffer[len_index] = offset - (len_index + 1);

    m_uart.send(buffer, offset);
}

