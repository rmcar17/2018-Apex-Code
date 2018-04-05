#ifndef VECTOR_H
#define VECTOR_H

class Vector {
  public:
    Vector();

    void setPolar(double magnitude, double angle);
    void setStandard(double _i, double _j);

    Vector operator+(Vector vector2);
    Vector operator-(Vector vector2);

    double i, j;
};

#endif
