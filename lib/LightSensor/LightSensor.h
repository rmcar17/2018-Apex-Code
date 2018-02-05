#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include <Arduino.h>

class LightSensor {
public:
	int threshold, pin, val;
	void setup(int inPin);
	void setThresh(int thresh);
	void setThresh(int low, int high);
	int getVal();
	bool onWhite();
}

#endif