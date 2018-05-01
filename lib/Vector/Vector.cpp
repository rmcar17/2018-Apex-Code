#include <Vector.h>

Vector::Vector(double val1, double val2, bool polar){
 polar ? setPolar(val1, val2) : setStandard(val1, val2);
}

void Vector::setStandard(double _i, double _j){
  i = _i;
  j = _j;

  mag = calcmag(_i, _j);
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
  return Vector(mag, arg) != Vector(0, 0);
}

double Vector::calcI(double _mag, double _arg){
  return _mag * cos(_arg);
}

double Vector::calcJ(double _mag, double _arg){
  return _mag * sin(_arg);
}

double Vector::calcmag(double _i, double _j){
  return sqrt(_i * _i + _j * _j);
}

double Vector::calcArg(double _i, double _j){
  return atan2(_j, _i);
}
