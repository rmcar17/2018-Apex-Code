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
	/*
	int calibration = 0;
	for(int ls = 0; ls < LS_NUM; ls++){
		// int total = 0;
		// for(int read_n = 0; read_n < LS_CALIBRATION_NUM; read_n++){
		// 	total += lightArray[ls].read();
		// }
		calibration = 1020;// constrain(round(total / LS_CALIBRATION_NUM + 150),0,1020);
		lightArray[ls].setThresh(calibration);
	}
	*/
	for(int i = 0; i < LS_NUM; i++){
		lightArray[i].setThresh(lightThresh[i]);
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

double LightSensorController::getVectorAngle(){
	if(vectorAngle==-1){
		return -1;
	}
	return mod(vectorAngle,360);
}


double LightSensorController::getLineAngle(){
	if(lineAngle==-1){
		return -1;
	}
	return mod(lineAngle,360);
}

void LightSensorController::setComp(int tempHeading){
	heading = mod(tempHeading,360);
}

void LightSensorController::setVector(int tempVector){
	if(tempVector==-1){
		vectorAngle = -1.00;
	} else{
		vectorAngle = (double)mod(tempVector+heading,360);
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
		if(danger == 1){
			if(inRange(vectorAngle,prevAngle,45)){
				initAngle = vectorAngle;
				lineAngle = vectorAngle;
			} else{
				danger = 2;
			}
		}
		else if(danger == 2){
			if(inRange(vectorAngle, initAngle,45)){
				lineAngle = initAngle;
				danger = 1;
			}
			else{
				lineAngle = initAngle;
			}
		}
	}
	else{
		if(danger<=1){
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

void LightSensorController::updateWithComp(){
	if(vectorAngle!=-1.00){
		a = inRange(vectorAngle,prevAngle,60);
		b = inRange(vectorAngle,initAngle,60);
		if(danger == 0){
			initAngle = vectorAngle;
			prevAngle = vectorAngle;
			lineAngle = vectorAngle;
			danger = 1;
		}
		if(danger == 1){
			if(a){
				initAngle = vectorAngle;
				lineAngle = vectorAngle;
			} else{
				danger = 2;
			}
		}
		else if(danger == 2){
			if(b){
				lineAngle = initAngle;
				danger = 1;
			}
			else{
				lineAngle = initAngle;
			}
		}
		prevAngle = vectorAngle;
	}
	else{
		if(danger<=1){
			initAngle = -1;
			vectorAngle = -1;
			lineAngle = -1;
			danger = 0;
			prevAngle = vectorAngle;
		}
		else{
			lineAngle = initAngle;
			vectorAngle = -1;
			prevAngle = vectorAngle;
		}
	}
}

void LightSensorController::updateOnWhite(){
	for(int i = 0; i < LS_NUM; i++){
		onWhite[i] = lightArray[i].onWhite();
	}
	if(onWhite[22]||onWhite[0]){
		onWhite[23] = 1;
	}else{
		onWhite[23] = 0;
	}
}

void LightSensorController::calcVectorAngle(){
	any = false;
	vectorX = 0;
	vectorY = 0;
	for(int i = 0; i < LS_NUM; i++){
		// bool exists = std::find(std::begin(brokenPins), std::end(brokenPins), i) != std::end(brokenPins);
		// if(!exists){
		if(onWhite[i]){
			any = true;
			vectorX += sin((450-i*(360/LS_NUM))*PI/180);
      		vectorY += cos((450-i*(360/LS_NUM))*PI/180);
		}
		// }
	}
	if(any){
		vectorAngle = correctRange(360-(180+(atan2(vectorY,vectorX)*180/PI)),0,360);
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