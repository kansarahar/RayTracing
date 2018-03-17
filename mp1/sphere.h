#ifndef SPHERE_H_
#define SPHERE_H_

#include "surface.h"
#include <string>
#include <cmath>


class Sphere: public Surface{
  public:
    Sphere();
    Sphere(float r, Vec c, Vec rgb);
    virtual bool hit(Ray& r, float tmin, float tmax) const;
    Vec center;
    float radius;
    std::string type;
    Vec color;
};

#endif
