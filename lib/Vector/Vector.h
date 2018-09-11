#ifndef VECTOR_H
#define VECTOR_H

#include <Common.h>
#include <Math.h>

class Vector {
  public:
    Vector(double val1, double val2, bool polar = true);

    void setStandard(double _i, double _j);
    void setPolar(double _mag, double _arg);

    Vector operator+(Vector vector2);
    Vector operator-(Vector vector2);
    Vector operator*(double scalar);
    Vector operator/(double scalar);

    bool operator==(Vector vector2);
    bool operator!=(Vector vector2);
    bool operator<(Vector vector2);
    bool operator<=(Vector vector2);
    bool operator>(Vector vector2);
    bool operator>=(Vector vector2);

    bool exists();
    bool exists(Vector ball);
    bool between(double leftAngle, double rightAngle);

    double i, j;
    double mag, arg;
  private:
    double calcI(double _mag, double _arg);
    double calcJ(double _mag, double _arg);

    double calcMag(double _i, double _j);
    double calcArg(double _i, double _j);
};

#endif
