#include <Vector.h>

Vector::Vector(){

}

void Vector::setStandard(double _i, double _j){
  i = _i;
  j = _j;
}

void Vector::setPolar(double magnitude, double argument){
  // Convert to standard and set i and j
  i = magnitude * cos(argument);
  j = magnitude * sin(argument);
}
