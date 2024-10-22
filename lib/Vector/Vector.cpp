#include <Vector.h>

Vector::Vector(double val1, double val2, bool polar){
 polar ? setPolar(val1, val2) : setStandard(val1, val2);
}

void Vector::setStandard(double _i, double _j){
  i = _i;
  j = _j;

  mag = calcMag(_i, _j);
  arg = calcArg(_i, _j);
}

void Vector::setPolar(double _mag, double _arg){
  // Convert to standard and set i and j
  i = calcI(_mag, _arg);
  j = calcJ(_mag, _arg);

  mag = _mag;
  arg = _arg;
}

Vector Vector::operator+(Vector vector2){
  return Vector(i + vector2.i, j + vector2.j, false);
}

Vector Vector::operator-(Vector vector2){
  return Vector(i - vector2.i, j - vector2.j, false);
}

Vector Vector::operator*(double scalar){
    return Vector(mag * scalar, arg);
}

Vector Vector::operator/(double scalar){
  return Vector(mag / scalar, arg);
}

bool Vector::operator==(Vector vector2){
  return mag == vector2.mag;
}

bool Vector::operator!=(Vector vector2){
  return mag != vector2.mag;
}

bool Vector::operator<(Vector vector2){
  return mag < vector2.mag;
}

bool Vector::operator<=(Vector vector2){
  return mag <= vector2.mag;
}

bool Vector::operator>(Vector vector2){
  return mag > vector2.mag;
}

bool Vector::operator>=(Vector vector2){
  return mag >= vector2.mag;
}

bool Vector::exists(){
  return mag != 0;
}

bool Vector::exists(Vector ball){
  return ball.mag != 0;
}

bool Vector::between(double leftAngle, double rightAngle){
  return isAngleBetween(arg, leftAngle, rightAngle);
}

double Vector::calcI(double _mag, double _arg){
  return _mag * sin(toRadians(_arg));
}

double Vector::calcJ(double _mag, double _arg){
  return _mag * cos(toRadians(_arg));
}

double Vector::calcMag(double _i, double _j){
  return sqrt(_i * _i + _j * _j);
}

double Vector::calcArg(double _i, double _j){
  return mod(360 + toDegrees(atan2(_j, _i)),360);
}
