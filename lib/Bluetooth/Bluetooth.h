#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>
#include <Defines.h>
#include <Timer.h>
#include <Vector.h>

class Bluetooth {
	public:
		Bluetooth();

		void setup();

		void send(char *t);
		void receive();

		Vector getOtherBallPos();
		Vector getOtherRobotPos();

	private:
		int receiveData[BT_DATA_SIZE] = {0};
		Timer timeout = Timer(BT_TIMEOUT);
};

#endif
