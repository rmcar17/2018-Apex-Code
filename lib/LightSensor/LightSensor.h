#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include <Arduino.h>

class LightSensor {
public:
	int threshold, pin, val;
	LightSensor();
	void setup(int inPin);
	void setThresh(int thresh);
	int getVal();
	bool onWhite();
};

#endif
