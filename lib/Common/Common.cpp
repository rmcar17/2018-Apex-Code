#include "Common.h"

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

/*int max(int x,int y){
  return x > y ? x : y;
}
*/