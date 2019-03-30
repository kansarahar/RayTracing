#ifndef SURFACE_H_
#define SURFACE_H_

#include "ray.h"
#include <string>

class Surface{
  public:
    virtual bool hit(Ray& r, float tmin, float tmax) const = 0;
    std::string type;
    Vec color;
    Vec center;

    Vec boundingMin;
    Vec boundingMax;
};


#endif
