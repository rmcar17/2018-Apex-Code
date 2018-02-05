#ifndef LIGHTSENSORCONTROLLER_H
#define LIGHTSENSORCONTROLLER_H

#include <Arduino.h>
#include <LightSensor.h>
#include <Common.h>
#include <Pins.h>


class LightSensorController {
	public:
		int onWhite[12];
		int lightValues[4] = {0};
  		int thresholds[4] = {0};
		LightSensor ls1;
		LightSensor ls2;
		LightSensor ls3;
		LightSensor ls4;
		LightSensor ls5;
		LightSensor ls6;
		LightSensor ls7;
		LightSensor ls8;
		LightSensor ls9;
		LightSensor ls10;
		LightSensor ls11;
		LightSensor ls12;

		void setup();
		void setThresh(thresh1,thresh2,thresh3,thresh4,thresh5,thresh6,thresh7,thresh8,thresh9,thresh10,thresh11,thresh12);
		void getVal();
}

#endif