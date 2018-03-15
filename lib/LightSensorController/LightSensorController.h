#ifndef LIGHTSENSORCONTROLLER_H
#define LIGHTSENSORCONTROLLER_H

#include <Arduino.h>
#include <LightSensor.h>
#include <Common.h>
#include <Pins.h>
#include <Defines.h>

class LightSensorController {
	public:
		LightSensorController();
		
		void setup();
		void read();

	private:
		void calibrate();

		int onWhite[LS_NUM];
		int lightValues[LS_NUM] = {0};
		LightSensor lightArray[LS_NUM] = {LightSensor()};
};

#endif
