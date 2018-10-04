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

		void send(int *pData);
		void receive();

		Vector getOtherBallPos();
		Vector getOtherRobotPos();

		Timer timeout = Timer(BT_TIMEOUT);
	private:
		int receiveData[BT_DATA_SIZE] = {0};
		Timer sendTime = Timer(BT_SEND_TIME);
};

#endif
