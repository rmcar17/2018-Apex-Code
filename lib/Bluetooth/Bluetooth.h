#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class Bluetooth{
public:
	void init();
	void send(uint8_t cmd);
	double receive();
private:
	double receiveCommand;
};

extern SoftwareSerial blueSerial;

#endif