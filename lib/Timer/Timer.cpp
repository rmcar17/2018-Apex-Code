#include "Timer.h"

Timer::Timer(unsigned long int timeLength){
  duration = timeLength;
  update();
}

void Timer::update(){
  startTime = micros();
}

bool Timer::hasTimePassed(){
  if(micros() - startTime > duration){
    update();
    return true;
  }
  return false;
}
