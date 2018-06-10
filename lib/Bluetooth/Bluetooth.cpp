#include "Bluetooth.h"

void Bluetooth::init(){
	blueSerial.begin(38400);
}

void Bluetooth::send(double cmd){
	blueSerial.write(cmd);
}
double Bluetooth::receive(){
	if (blueSerial.available())
	{
		receiveCommand = blueSerial.read();
	}
	return receiveCommand;
}