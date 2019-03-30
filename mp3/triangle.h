#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "surface.h"
#include <string>
#include <cmath>


class Triangle: public Surface{
  public:
    Triangle();
    Triangle(Vec Aval, Vec Bval, Vec Cval, Vec rgb);
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
