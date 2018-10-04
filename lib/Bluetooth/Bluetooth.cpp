#include "Bluetooth.h"

Bluetooth::Bluetooth(){

}

void Bluetooth::setup(){
	Serial3.begin(38400);
}

void Bluetooth::send(int *pData){
	if(sendTime.hasTimePassed()){
		Serial3.write(BT_START_1);
		Serial3.write(BT_START_2);
		for(int i=0; i<BT_DATA_SIZE; i++){
			Serial3.write((*(pData+i)) & 0xFF);
			Serial3.write((*(pData+i)) >> 8);
		}
	}
}

void Bluetooth::receive(){
	if(Serial3.available() > 4 * BT_DATA_SIZE){
		while(Serial3.read() != BT_START_1 && Serial3.peek() != BT_START_2){
			if(Serial3.available() < BT_DATA_SIZE){
				return;
			}
		}
		Serial3.read();

		timeout.update();

		for(int i = 0; i<BT_DATA_SIZE; i++){
			uint8_t byte1 = Serial3.read();
			uint8_t byte2 = Serial3.read();
			receiveData[i] = (byte2 << 8) | byte1;
		}
	}
}

bool Bluetooth::isConnected(){
	return !timeout.hasTimePassedNoUpdate();
}

Vector Bluetooth::getOtherBallPos(){
	if(isConnected()){
		return Vector(receiveData[0],receiveData[1],false);
	}
	else{
		return Vector(0,0);
	}
}

Vector Bluetooth::getOtherRobotPos(){
	if(isConnected()){
		return Vector(receiveData[2],receiveData[3],false);
	}
	else{
		return Vector(0,0);
	}
}
