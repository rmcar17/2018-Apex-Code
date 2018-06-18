#include <Arduino.h>
#include <Defines.h>
#include <t3spi.h>
#include <LightSensor.h>
#include <LightSensorController.h>
#include <Bluetooth.h>

SoftwareSerial blueSerial(7,8);

LightSensorController lights;
T3SPI spi;
Bluetooth bt;

int ledPin = 13;
uint16_t balli, ballj;
int pos = 0;


void setup(){
  Serial.begin(38400);
  spi.begin_SLAVE(SLAVE_LIGHT_SCK, SLAVE_LIGHT_MOSI, SLAVE_LIGHT_MISO, SLAVE_LIGHT_CS);
  spi.setCTAR_SLAVE(16, SPI_MODE0);
  NVIC_ENABLE_IRQ(IRQ_SPI0);
  lights.setup();
  bt.init();
}

void loop(){
  lights.update();
  // bt.send(1);
  // bt.send(250);
  // bt.send(2);
  // bt.send(123);
  double var = bt.receive();
  if(var == 1){
    pos = 1;
  } else if (var == 2){
    pos = 2;
  } else{
    if(pos == 1){
      balli = var;
    } else if(pos == 2){
      ballj = var;
    }
  }

  // balli = 70;
  // ballj = 170;

  // Serial.print(ballAngle);
  // Serial.print("\t");
  // Serial.println(ballDistance);



  for(int i = 0; i < LS_NUM; i++){
    Serial.print(lights.onWhite[i]);
    Serial.print("\t");
  }
  Serial.println();
}

void spi0_isr(){
  uint16_t dataIn = SPI0_POPR;

  uint8_t command = (dataIn >> 14);
  uint16_t data = (dataIn & 0x3FFF);

  uint16_t dataOut = 0;

  uint16_t lightVector;

  lightVector = (uint16_t)((int)lights.getVectorAngle());

  switch(command){
  case 0:
    dataOut = lightVector;
    break;
  // case 1:
  //   bt.send((uint16_t)1);
  //   bt.send((uint16_t(data)));
  //   dataOut = (uint16_t)balli;
  //   break;
  // case 2:
  //   bt.send((uint16_t)2);
  //   bt.send((uint16_t(data)));
  //   dataOut = (uint16_t)ballj;
  //   break;
  default:
    dataOut = (uint16_t)69;
    break;
  }

  SPI0_PUSHR_SLAVE = dataOut;
  SPI0_SR |= SPI_SR_RFDF;
}
