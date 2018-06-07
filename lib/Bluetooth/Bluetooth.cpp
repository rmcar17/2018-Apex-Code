#include "Bluetooth.h"

void Bluetooth::init(){
	blueSerial.begin(38400);
}

void Bluetooth::send(double cmd){
	if (Serial.available())
	{
		blueSerial.write(cmd);
	}
}
void Bluetooth::receive(){
	if (blueSerial.available())
	{
		receiveCommand = blueSerial.read();
	}
	return receiveCommand;
}