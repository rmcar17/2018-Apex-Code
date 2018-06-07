#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial blueSerial(7, 8);

class Blutooth{
public:
	SoftwareSerial blueSerial(7,8);
	void init();
	void send(double cmd);
	double receive();
private:
	double receiveCommand;
}