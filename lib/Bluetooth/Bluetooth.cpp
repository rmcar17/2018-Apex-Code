#include "Bluetooth.h"

Bluetooth::Bluetooth(){

}

void Bluetooth::setup(){
	Serial3.begin(38400);
}

void Bluetooth::send(char *t){
	Serial3.write(*t);
}

void Bluetooth::receive(){
	Serial.println(Serial3.read());
	// if(Serial3.available() > 2 * BT_DATA_SIZE){
	// 	while(Serial3.read() != BT_START && Serial3.available());
	//
	// 	if(Serial3.available() < BT_DATA_SIZE){
	// 		return;
	// 	}
	//
	// 	timeout.update();
	//
	// 	for(int i = 0; i<BT_DATA_SIZE; i++){
	// 		receiveData[i] = Serial3.read();
	// 	}
	// }
}

Vector Bluetooth::getOtherBallPos(){
	if(timeout.hasTimePassedNoUpdate()){
		return Vector(0,0);
	}
	else{
		return Vector(receiveData[0],receiveData[1],false);
	}
}

Vector Bluetooth::getOtherRobotPos(){
	if(timeout.hasTimePassedNoUpdate()){
		return Vector(0,0);
	}
	else{
		return Vector(receiveData[2],receiveData[3],false);
	}
}
