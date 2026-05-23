/*
 * sensor.hpp
 *
 *  Created on: 10.05.2026
 *      Author: valen
 */

#ifndef PERIPHERALS_SENSOR_HPP_
#define PERIPHERALS_SENSOR_HPP_

class Sensor {
public:
	bool isReady_ = false;
	virtual void init() {};
	void calibrate() {
		if (!isReady_) {
			_calibrate();
		}
	};
private:
	virtual void _calibrate() {isReady_ = true;}
};


#endif /* PERIPHERALS_SENSOR_HPP_ */
