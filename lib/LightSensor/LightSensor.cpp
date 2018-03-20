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
	readVal = analogRead(pin);
	return readVal;
}

bool LightSensor::onWhite(){
	return readVal > 1000 ? true : false;
}
