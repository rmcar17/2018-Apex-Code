#include "LightSensorController.h"

void LightSensorController::setup(){
	for(int i = 0; i < LS_NUM; i++){
		lightArray[i].setup(lightPins[i]);
		Serial.print("LightSensor[");
		Serial.print(lightPins[i]);
		Serial.println("] is on");
	}
	setThresh();
}

void LightSensorController::setThresh(){
	for(int lCount = 0; lCount < LS_NUM; lCount++){
		int total = 0;
		for(int cCount = 0; cCount < CALI_NUM; cCount++){
			total += lightArray[lCount].read();
		}
		int cali = round(total / CALI_NUM) + 20;

		lightArray[lCount].setThresh(cali);
	}
}

void LightSensorController::read(){
	for(int i = 0; i < LS_NUM; i++){
		lightValues[i] = lightArray[i].read();
	}
}
