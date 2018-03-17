#include "rectangle.h"
#include <string>
#include <cmath>
#include <iostream>

Rectangle::Rectangle(){
  type = "Rectangle";
}

Rectangle::Rectangle(Vec Aval, Vec Bval, Vec Cval, Vec rgb){
  A = Aval;
  B = Bval;
  C = Cval;
  color = rgb;
}

bool Rectangle::hit(const Vec& p) const{
  Vec ba = B-A;
  Vec ca = C-A;
  Vec pa = p-A;
  Vec normal = ba.cross(ca);
  normal.make_unit();

  float area = ba.cross(ca).magnitude()*0.5;
  float u = ba.cross(pa).dot(normal)*0.5;
  float v = pa.cross(ca).dot(normal)*0.5;
  float w = area - u - v;

  Vec Aopp = A + ba + ca;
  Vec Bopp = C;
  Vec Copp = B;

  Vec baopp = Bopp-Aopp;
  Vec caopp = Copp-Aopp;
  Vec paopp = p - Aopp;

  float areaopp = baopp.cross(caopp).magnitude()*0.5;
  float uopp = baopp.cross(paopp).dot(normal)*0.5;
  float vopp = paopp.cross(caopp).dot(normal)*0.5;
  float wopp = areaopp - uopp - vopp;

  if ((u > 0 && v > 0 && w > 0)||(uopp > 0 && vopp > 0 && wopp > 0)){
    return true;
  }
  return false;
}

bool Rectangle::hit(Ray& r, float tmin, float tmax) const{
  Vec ao = A - r.origin();
  Vec ba = B-A;
  Vec ca = C-A;
  Vec normal = ba.cross(ca);


  float t1 = (ao.dot(normal))/(r.direction().dot(normal));

  if (t1 > tmin && t1 < tmax){
    if (hit(r.point_at_t(t1))){
      Hit_Record* RectangleHit = new Hit_Record(t1, r.point_at_t(t1), normal.unit(), color);
      r.hrl.addHR(*RectangleHit);
      return true;
    }
  }
  return false;
}
