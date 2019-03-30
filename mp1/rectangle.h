#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "surface.h"
#include <string>
#include <cmath>


class Rectangle: public Surface{
  public:
    Rectangle();
    Rectangle(Vec Aval, Vec Bval, Vec Cval, Vec rgb);
    virtual bool hit(Ray& r, float tmin, float tmax) const;
    Vec A;
    Vec B;
    Vec C;
    std::string type;
    Vec color;
  private:
    bool hit(const Vec& p) const;
};

#endif
