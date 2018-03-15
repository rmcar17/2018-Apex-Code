#include "LightSensorController.h"

LightSensorController::LightSensorController(){
	
}

void LightSensorController::setup(){
	for(int i = 0; i < LS_NUM; i++){
		lightArray[i].setup(lightPins[i]);
		Serial.print("LightSensor[");
		Serial.print(lightPins[i]);
		Serial.println("] is on");
	}
	calibrate();
}

void LightSensorController::calibrate(){
	int calibration;
	for(int ls = 0; ls < LS_NUM; ls++){
		int total = 0;
		for(int read_n = 0; read_n < LS_CALIBRATION_NUM; read_n++){
			total += lightArray[ls].read();
		}
		calibration = round(total / LS_CALIBRATION_NUM) + 20;

		lightArray[ls].setThresh(calibration);
	}
}

void LightSensorController::read(){
	for(int i = 0; i < LS_NUM; i++){
		lightValues[i] = lightArray[i].read();
	}
}
