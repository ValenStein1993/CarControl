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
#include "datatypes.hpp"

enum class DataType: uint8_t {
	e_bool,
	e_uint8,
    e_int16,
    e_float,
    e_q4_12
};

struct LogVariable {
	const char* varName;
	void* ptrVal;
	size_t size;
	DataType varType;
};

template<typename T>
struct TypeMap {
    static constexpr DataType value = DataType::e_bool;
};

template<>
struct TypeMap<int16_t> {
    static constexpr DataType value = DataType::e_int16;
};

template<>
struct TypeMap<uint8_t> {
    static constexpr DataType value = DataType::e_uint8;
};

template<>
struct TypeMap<float> {
    static constexpr DataType value = DataType::e_float;
};

template<>
struct TypeMap<q4_12_t> {
    static constexpr DataType value = DataType::e_q4_12;
};

class DataLogger {
public:
	DataLogger(Uart& uart);

    void serialize(uint8_t* buffer, size_t& size);
    void log();
    void sendConfig();

    template<typename T>
    void addVariable(const char* name, T* ptr) {
    	m_variables.push_back({name, ptr, sizeof(T), TypeMap<T>::value});
    }

private:
    std::vector<LogVariable> m_variables;
    Uart& m_uart;
};


#endif /* INC_DATALOGGER_HPP_ */

