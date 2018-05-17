#include <Arduino.h>
#include <Defines.h>
#include <t3spi.h>
#include <LightSensor.h>
#include <LightSensorController.h>


LightSensorController lights;
T3SPI spi;

int ledPin = 13;


void setup(){
	Serial.begin(9600);
	spi.begin_SLAVE(SLAVE_LIGHT_SCK, SLAVE_LIGHT_MOSI, SLAVE_LIGHT_MISO, SLAVE_LIGHT_CS);
	spi.setCTAR_SLAVE(16, SPI_MODE0);
	NVIC_ENABLE_IRQ(IRQ_SPI0);
	lights.setup();
	pinMode(ledPin,OUTPUT);
}

void loop(){
	lights.update();
	digitalWrite(ledPin,HIGH);
}

void spi0_isr(){
	uint16_t dataIn = SPI0_POPR;

	uint8_t command = (dataIn >> 10);
	uint16_t data = (dataIn & 0x3FF);

	uint16_t dataOut = 0;

	uint16_t lightVector;

	if(lights.vectorAngle<0){
		lightVector = (uint16_t)69;
	}else{
		lightVector = (uint16_t)((int)lights.vectorAngle);
	}

	
	
	uint16_t lightLine = (int)lights.lineAngle;

	switch(command){
	case 0:
		dataOut = lightVector;
		break;
	default:
		dataOut = (uint16_t)69;
		break;
	}

	SPI0_PUSHR_SLAVE = dataOut;
	SPI0_SR |= SPI_SR_RFDF;
}