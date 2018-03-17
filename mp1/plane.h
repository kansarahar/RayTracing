#ifndef PLANE_H_
#define PLANE_H_

#include "surface.h"
#include <string>
#include <cmath>


class Plane: public Surface{
  public:
    Plane();
    Plane(Vec n, Vec a, Vec rgb);
    virtual bool hit(Ray& r, float tmin, float tmax) const;
    Vec n_;
    Vec a_;
    std::string type;
    Vec color;
};

#endif
