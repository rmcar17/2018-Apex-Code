#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include <Arduino.h>

class LightSensor {
	public:
		LightSensor();

		void setup(int inPin);
		void setThresh(int thresh);
		int read();
		bool onWhite();

	private:
		int threshold, pin, readVal;
};

#endif
