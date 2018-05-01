#include <Vector.h>

Vector::Vector(double val1, double val2, bool polar){
 polar ? setPolar(val1, val2) : setStandard(val1, val2);
}

void Vector::setStandard(double _i, double _j){
  i = _i;
  j = _j;

  mod = calcMod(_i, _j);
  arg = calcArg(_i, _j);
}

void Vector::setPolar(double _mod, double _arg){
  // Convert to standard and set i and j
  i = calcI(_mod, _arg);
  j = calcJ(_mod, _arg);

  mod = _mod;
  arg = _arg;
}

Vector Vector::operator+(Vector vector2){
  return Vector(i + vector2.i, j + vector2.j, false);
}

Vector Vector::operator-(Vector vector2){
  return Vector(i - vector2.i, j - vector2.j, false);
}

double Vector::calcI(double _mod, double _arg){
  return _mod * cos(_arg);
}

double Vector::calcJ(double _mod, double _arg){
  return _mod * sin(_arg);
}

double Vector::calcMod(double _i, double _j){
  return sqrt(_i * _i + _j * _j);
}

double Vector::calcArg(double _i, double _j){
  return atan2(_j, _i);
}
