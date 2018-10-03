#include <Kicker.h>

Kicker::Kicker(){

}

void Kicker::setup(){
  pinMode(KICKER_PIN, OUTPUT);
  digitalWrite(KICKER_PIN, LOW);
}

void Kicker::kick(){
  if(kickInterval.hasTimePassed()){
    digitalWrite(KICKER_PIN, HIGH);
    kickLow.update();
  }
}

void Kicker::resetKicker(){
  if(kickLow.hasTimePassed()){
    digitalWrite(KICKER_PIN, LOW);
  }
}
