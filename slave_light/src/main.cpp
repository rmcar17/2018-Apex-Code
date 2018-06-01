#include <Arduino.h>
const int lightPins[24] = {33,34,35,36,37,38,39,21,22,15,16,17,32,31,49,50,18,19,20,21,22,23,A11,A10};

void LightSetup(int inPin){
  int pin = inPin;
  pinMode(pin,INPUT);
}

int LightRead(int inPin){
  int pin = inPin;
  int readVal = analogRead(pin);
}
void setup() {
  Serial.begin(9600);
  for(int i = 0; i < 24; i++){
    LightSetup(lightPins[i]);
  }
}

void loop() {
  for(int i = 0; i < 24; i++){
    Serial.print(LightRead(lightPins[i]));
    Serial.print(" ");
  }
  Serial.println();
}
