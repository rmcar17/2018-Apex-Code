#include <Vector.h>

Vector::Vector(){

}

void Vector::setStandard(double _i, double _j){
  i = _i;
  j = _j;
}

void Vector::setPolar(double _mod, double _arg){
  // Convert to standard and set i and j
  i = _mod * cos(_arg);
  j = _mod * sin(_arg);

  mod = _mod;
  arg = _arg;
}
