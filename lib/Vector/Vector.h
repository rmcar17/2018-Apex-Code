#ifndef VECTOR_H
#define VECTOR_H

#include <Math.h>

class Vector {
  public:
    Vector(double val1, double val2, bool polar = true);

    void setStandard(double _i, double _j);
    void setPolar(double _mod, double _arg);

    Vector operator+(Vector vector2);
    Vector operator-(Vector vector2);

    double i, j;
    double mod, arg;
  private:
    double calcI(double _mod, double _arg);
    double calcJ(double _mod, double _arg);

    double calcMod(double _i, double _j);
    double calcArg(double _i, double _j);
};

#endif
