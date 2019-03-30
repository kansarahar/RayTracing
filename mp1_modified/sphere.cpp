#include "sphere.h"
#include <string>
#include <cmath>

Sphere::Sphere(){
  type = "sphere";
}

Sphere::Sphere(float r, Vec c, Vec rgb){
  radius = r;
  center = c;
  color = rgb;
}


bool Sphere::hit(Ray& r, float tmin, float tmax) const{
  Vec oc = r.origin() - center;
  float a = r.direction().dot(r.direction());
  float b = 2*oc.dot(r.direction());
  float c = oc.dot(oc) - radius*radius;
  float discriminant = b*b-4*a*c;
  if (discriminant > 0){
    float t2 = (-1*b - sqrt(discriminant))/(2*a);
    float t1 = (-1*b + sqrt(discriminant))/(2*a);
    if (t2 > tmin && t2 < tmax){
      Hit_Record sphereHit(t2, r.point_at_t(t2), (r.point_at_t(t2)-center).make_unit(), color);
      r.hitRecordList.push_back(sphereHit);
      return true;
    }
    else{
      if (t1 > tmin && t1 < tmax){
        Hit_Record sphereHit(t1, r.point_at_t(t1), (r.point_at_t(t1)-center).make_unit(), color);
        r.hitRecordList.push_back(sphereHit);
        return true;
      }
    }
  }
  return false;
}
