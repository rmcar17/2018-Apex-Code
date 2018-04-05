#include <Vector.h>

Vector::Vector(){

}

void Vector::setStandard(double _i, double _j){
  i = _i;
  j = _j;

  mod = sqrt(_i * _i + _j * _j);
  arg = atan2(_j, _i)
}

void Vector::setPolar(double _mod, double _arg){
  // Convert to standard and set i and j
  i = _mod * cos(_arg);
  j = _mod * sin(_arg);

  mod = _mod;
  arg = _arg;
}
