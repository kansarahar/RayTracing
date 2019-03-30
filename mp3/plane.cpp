#include "plane.h"
#include <string>
#include <cmath>

Plane::Plane(){
  type = "Plane";
}

Plane::Plane(Vec n, Vec a, Vec rgb){
  n_ = n;
  a_ = a;
  color = rgb;
}


bool Plane::hit(Ray& r, float tmin, float tmax) const{
  Vec ao = a_ - r.origin();
  float t1 = (ao.dot(n_))/(r.direction().dot(n_));
  if (t1 > tmin && t1 < tmax){
    Hit_Record* hr = new Hit_Record(t1, r.point_at_t(t1), n_.unit(), color);
    r.hitRecordList.push_back(hr);
    return true;
  }
  return false;
}
