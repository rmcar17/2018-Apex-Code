#include "Common.h"
#include <math.h>


double toDegrees(double rad){
  return rad*TO_DEGREES;
}

double toRadians(double deg){
  return deg*TO_RADIANS;
}

int mod(int n, int modulo){
  int r = n % modulo;
  return r < 0 ? r + modulo : r;
}

double doubleMod(double value, double maxValue) {
    return fmod((value + maxValue), maxValue);
}

bool isAngleBetween(int angle, int leftAngle, int rightAngle){
  if(rightAngle < leftAngle){
    return angle < rightAngle || angle > leftAngle;
  }
  else{
    return angle < rightAngle && angle > leftAngle;
  }
}

/*int max(int x,int y){
  return x > y ? x : y;
}
*/
