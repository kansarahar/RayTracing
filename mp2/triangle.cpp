#include "triangle.h"
#include <string>
#include <cmath>
#include <iostream>

Triangle::Triangle(){
  type = "Triangle";
}

float findMin(float x1, float x2, float x3){
  if (x1 <= x2 && x1 <= x3){
    return x1;
  }
  else{
    if (x2 <= x1 && x2 <= x3){
      return x2;
    }
  }
  return x3;
}

float findMax(float x1, float x2, float x3){
  if (x1 >= x2 && x1 >= x3){
    return x1;
  }
  else{
    if (x2 >= x1 && x2 >= x3){
      return x2;
    }
  }
  return x3;
}
Triangle::Triangle(Vec Aval, Vec Bval, Vec Cval, Vec rgb){
  A = Aval;
  B = Bval;
  C = Cval;
  color = rgb;

  boundingMin = Vec(findMin(A.x(), B.x(), C.x()), findMin(A.y(), B.y(), C.y()), findMin(A.z(), B.z(), C.z()));
  boundingMax = Vec(findMax(A.x(), B.x(), C.x()), findMax(A.y(), B.y(), C.y()), findMax(A.z(), B.z(), C.z()));
}

bool Triangle::hit(const Vec& p) const{
  Vec ba = B-A;
  Vec ca = C-A;
  Vec pa = p-A;
  Vec normal = ba.cross(ca);
  normal.make_unit();
  float area = ba.cross(ca).magnitude()*0.5;
  float u = ba.cross(pa).dot(normal)*0.5;
  float v = pa.cross(ca).dot(normal)*0.5;
  float w = area - u - v;
  if (u > 0 && v > 0 && w > 0){
    return true;//if (u+v+w == 1){return true;}
  }
  return false;
}

bool Triangle::hit(Ray& r, float tmin, float tmax) const{
  Vec ao = A - r.origin();
  Vec ba = B-A;
  Vec ca = C-A;
  Vec normal = ba.cross(ca);


  float t1 = (ao.dot(normal))/(r.direction().dot(normal));

  if (t1 > tmin && t1 < tmax){
    if (hit(r.point_at_t(t1))){
      Hit_Record* hr = new Hit_Record(t1, r.point_at_t(t1), normal.unit(), color);
      r.hitRecordList.push_back(hr);
      return true;
    }
  }
  return false;
}
