#include "LightSensor.h"

void LightSensor::setup(int inPin){
	pin = inPin;
	pinMode = (pin,INPUT);
}

void LightSensor::setThresh(int thresh){
	threshold = thresh;
}

void LightSensor::setThresh(int low, int high){
	threshold = ((low+high)/2);
}

int LightSensor::getVal(){
	val = analogRead(pin);
	return val;
}

bool LightSensor::onWhite(){
	return val > threshold ? true : false;
}