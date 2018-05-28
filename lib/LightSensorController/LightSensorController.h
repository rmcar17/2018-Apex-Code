#ifndef LIGHTSENSORCONTROLLER_H
#define LIGHTSENSORCONTROLLER_H

#include <Arduino.h>
#include <LightSensor.h>
#include <Common.h>
#include <Pins.h>
#include <Defines.h>
#include <algorithm> // for std::find
#include <iterator> // for std::begin, std::end

class LightSensorController {
	public:
		LightSensorController();
		void setup();
		void update();
		void updateWithComp();
		double getVectorAngle();
		double getLineAngle();
		void setComp(int tempHeading);
		void setVector(int tempVector);
		int lightValues[LS_NUM] = {0};
		int onWhite[LS_NUM] = {0};
	//private:
		void calibrate();
		int correctRange(int value, int max);
		int correctRange(int value, int min, int max);
		int correctAngleRange(int value, int min, int max);
		void calcVectorAngle();
		void setDangers(int init);
		void updateOnWhite();
		bool inRange(double value, double target, int range);
		void read();
		LightSensor lightArray[LS_NUM] = {LightSensor()};
		bool any;
		double vectorX, vectorY;
		double initAngle;
		double prevAngle;
		double vectorAngle;
		double lineAngle;
		int danger = 0;
		int heading = 0;
		bool a;
};

#endif
