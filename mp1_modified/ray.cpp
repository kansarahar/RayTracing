#include "ray.h"
#include <vector>
Ray::Ray(){

}

Ray::~Ray(){
}

Ray::Ray(const Vec& o, const Vec& d){
  o_ = o;
  d_ = d;
}

Vec Ray::origin() const{
  return o_;
}

Vec Ray::direction() const{
  return d_;
}

Vec Ray::point_at_t(float t){
  return o_ + d_*t;
}



Hit_Record::Hit_Record(float tval, const Vec& p, const Vec& n, const Vec& c){
  t = tval;
  point = Vec(p);
  normal = Vec(n);
  color = Vec(c);
}

Hit_Record::Hit_Record(const Hit_Record& other){
  t = other.t;
  point = Vec(other.point);
  normal = Vec(other.normal);
  color = Vec(other.color);
}

Hit_Record::~Hit_Record(){
}



Hit_Record Ray::find_first_hit() const{
  Hit_Record min = hitRecordList[0];
  for (int i = 0; i < hitRecordList.size(); i++){
    if (min.t > hitRecordList[i].t){
      min = hitRecordList[i];
    }
  }
  return min;
}
