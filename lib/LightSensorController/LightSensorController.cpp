#include "LightSensorController.h"

LightSensorController::LightSensorController(){

}

void LightSensorController::setup(){
	for(int i = 0; i < LS_NUM; i++){
		lightArray[i].setup(lightPins[i]);
		#if DEBUG_LIGHT
			Serial.print("LightSensor[");
			Serial.print(lightPins[i]);
			Serial.println("] is on");
		#endif
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
		calibration = round(total / LS_CALIBRATION_NUM) + 100;

		lightArray[ls].setThresh(1000);
	}
}

void LightSensorController::read(){
	for(int i = 0; i < LS_NUM; i++){
		lightValues[i] = lightArray[i].read();
		#if DEBUG_LIGHT
			Serial.print("LS");
			Serial.print(i);
			Serial.print(": ");
			Serial.print(lightValues[i]);
		#endif
	}
}

void LightSensorController::update(){
	read();
	updateOnWhite();
	calcVectorAngle();
	if(any){
		if(danger==0){
			initAngle = vectorAngle;
			prevAngle = vectorAngle;
			lineAngle = vectorAngle;
			danger = 1;
		}
		if(danger >= 1 && danger <= 4){
			if(inRange(vectorAngle,prevAngle,90)){
				initAngle = vectorAngle;
				lineAngle = vectorAngle;
			} else{
				danger = 5;
			}
		}
		else if(danger >= 5 && danger <= 7){
			if(inRange(vectorAngle, initAngle, 90)){
				lineAngle= initAngle;
				danger = 1;
			}
			else{
				initAngle = correctRange(vectorAngle+180,0,360);
				lineAngle = initAngle;
			}
		}
	}
	else{
		if(danger<=4){
			initAngle = -1;
			vectorAngle = -1;
			lineAngle = -1;
			danger = 0;
		}
		else{
			lineAngle = initAngle;
			vectorAngle = -1;
		}
	}
	prevAngle = vectorAngle;
}

void LightSensorController::updateOnWhite(){
	for(int i = 0; i < LS_NUM; i++){
		onWhite[i] = lightArray[i].onWhite();
	}
}

void LightSensorController::calcVectorAngle(){
	any = false;
	vectorX = 0;
	vectorY = 0;
	for(int i = 0; i < LS_NUM; i++){
		if(onWhite[i]){
			any = true;
			vectorX += sin((450-i*(360/LS_NUM))*PI/180);
      		vectorY += cos((450-i*(360/LS_NUM))*PI/180);
		}
	}
	if(any){
		vectorAngle = correctRange((atan2(vectorY,vectorX)*180/PI),0,360);
	}
	else{
		vectorAngle = -1;
	}
}

bool LightSensorController::inRange(double value, double target, int range){
    double offset = value;
    value = 0;
    target = correctRange(target-offset, 0, 360);
    if(target <= range || target >= 360-range){
        return true;
    }
    else{
        return false;
    }
}

int LightSensorController::correctRange(int value, int max){
	if(value > max){
		while(value > max){
			value -= max;
		}
	}
	return value;
}

int LightSensorController::correctRange(int value, int min, int max){
	if(value > max){
        while(value > max){
            value -= max;
        }
    }
    if(value < min){
        while(value < min){
            value += max;
        }
    }
    return value;
}

int LightSensorController::correctAngleRange(int value, int min, int max){
    if(value > max){
        while(value > max){
            value -= max + 1;
        }
    }
    if(value < min){
        while(value < min){
            value += max + 1;
        }
    }
    return value;
}
