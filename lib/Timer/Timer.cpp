#include "Timer.h"

Timer::Timer(unsigned int timeLength){
  duration = timeLength;
  update();
}

void Timer::update(){
  startTime = millis();
}

bool Timer::hasTimePassed(){
  if(millis() - startTime > duration){
    update();
    return true;
  }
  return false;
}
