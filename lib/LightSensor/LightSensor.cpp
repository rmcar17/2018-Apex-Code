#include "LightSensor.h"

LightSensor::LightSensor(){

}

void LightSensor::setup(int inPin){
	pin = inPin;
	pinMode(pin,INPUT);
}

void LightSensor::setThresh(int thresh){
	threshold = thresh;
}

int LightSensor::read(){
	val = analogRead(pin);
	return val;
}

bool LightSensor::onWhite(){
	return val > threshold ? true : false;
}
