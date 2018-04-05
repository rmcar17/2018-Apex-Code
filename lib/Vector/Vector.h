#ifndef VECTOR_H
#define VECTOR_H

#include <Math.h>

class Vector {
  public:
    Vector();

    void setStandard(double _i, double _j);
    void setPolar(double _mod, double _arg);

    Vector operator+(Vector vector2);
    Vector operator-(Vector vector2);

    double i, j;
    double mod, arg;
};

#endif
