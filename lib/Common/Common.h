#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>

#define PI 3.14159265358979323846264338327950

#define TO_RADIANS 0.01745329251994329576923690768489
#define TO_DEGREES 57.29577951308232087679815481410517


double toDegrees(double rad);
double toRadians(double deg);

int mod(int n, int modulo);
double doubleMod(double value, double maxValue);

//int max(int x, int y);

struct Vector3D {
  double x;
  double y;
  double z;
};

struct Vector4D {
	double r;
	double g;
	double b;
	double a;
}

#endif
