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
		int lightValues[LS_NUM] = {0};
		bool onWhite[LS_NUM] = {false};
		void update();
		void updateOnWhite();
		bool inRange(double value, double target, int range);
		void setDangers(int init);
		int correctRange(int value, int max);
		int correctRange(int value, int min, int max);
		int correctAngleRange(int value, int min, int max);
		void calcVectorAngle();
	//private:
		void calibrate();
		LightSensor lightArray[LS_NUM] = {LightSensor()};
		bool any;
		double vectorX, vectorY;
		double vectorAngle;
		double initAngle;
		double prevAngle;
		double lineAngle;
		int danger = 0;
};

#endif
