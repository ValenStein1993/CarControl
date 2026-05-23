/*
 * Scheduler.cpp
 *
 *  Created on: 05.03.2026
 *      Author: valen
 */

#include "scheduler.hpp"
#include "datatypes.hpp"

extern float dt;

Scheduler::Scheduler()
{
	sum100 = 0;
	sum1000 = 0;
	tick10ms = 0;
	tick100ms = 0;
	tick1000ms = 0;

}

void Scheduler::update() {
	tick10ms++;
	if (++sum100 >= 10) {
		sum100 = 0;
		tick100ms++;
	}

	if (++sum1000 >= 100) {
		sum1000 = 0;
		tick1000ms++;
	}
}

bool Scheduler::run10ms() {
	if (tick10ms) {
		tick10ms--;
		dt = 0.01;
		return true;
	}
	else {
		return false;
	}
}

bool Scheduler::run100ms() {
	if (tick100ms) {
		tick100ms--;
		dt = 0.1;
		return true;
	}
	else {
		return false;
	}
}

bool Scheduler::run1000ms() {
	if (tick1000ms) {
		tick1000ms--;
		dt = 1;
		return true;
	}
	else {
		return false;
	}
}
