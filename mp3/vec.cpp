#include "vec.h"
#include <cmath>
#include <iostream>

Vec::Vec(){
  e[0] = 0;
  e[1] = 0;
  e[2] = 0;
}
Vec::Vec(float x, float y, float z){
  e[0] = x;
  e[1] = y;
  e[2] = z;
}

Vec::Vec(const Vec& other){
  e[0] = other.e[0];
  e[1] = other.e[1];
  e[2] = other.e[2];
}

Vec::~Vec(){
}

float Vec::x() const {return e[0];}
float Vec::y() const {return e[1];}
float Vec::z() const {return e[2];}

float Vec::r() const {return e[0];}
float Vec::g() const {return e[1];}
float Vec::b() const {return e[2];}


const Vec& Vec::operator+() const {return *this;}
Vec Vec::operator-() const {return Vec(-1*e[0], -1*e[1], -1*e[2]);}
float& Vec::operator[](int i) {return e[i];}

Vec Vec::operator+(const Vec& v2) const{
  return Vec(e[0] + v2.e[0], e[1] + v2.e[1], e[2] + v2.e[2]);
}
Vec Vec::operator-(const Vec& v2) const{
  return Vec(e[0] - v2.e[0], e[1] - v2.e[1], e[2] - v2.e[2]);
}
Vec Vec::operator*(const Vec& v2) const{
  return Vec(e[0] * v2.e[0], e[1] * v2.e[1], e[2] * v2.e[2]);
}
Vec Vec::operator/(const Vec& v2) const{
  return Vec(e[0] / v2.e[0], e[1] / v2.e[1], e[2] / v2.e[2]);
}

bool Vec::operator==(const Vec& v2) const{
  return (e[0] == v2.e[0] && e[1] == v2.e[1] && e[2] == v2.e[2]);
}


Vec Vec::operator*(float c) const{
  return Vec(c*e[0], c*e[1], c*e[2]);
}

Vec Vec::operator/(float c) const{
  if (c == 0){return Vec(0,0,0);}
  return Vec(e[0]/c, e[1]/c, e[2]/c);
}


Vec Vec::operator+=(const Vec& v2){
  e[0] = e[0] + v2.e[0];
  e[1] = e[1] + v2.e[1];
  e[2] = e[2] + v2.e[2];
  return *this;
}

Vec Vec::operator-=(const Vec& v2){
  e[0] = e[0] - v2.e[0];
  e[1] = e[1] - v2.e[1];
  e[2] = e[2] - v2.e[2];
  return *this;
}

Vec Vec::operator*=(const Vec& v2){
  e[0] = e[0] * v2.e[0];
  e[1] = e[1] * v2.e[1];
  e[2] = e[2] * v2.e[2];
  return *this;
}

Vec Vec::operator/=(const Vec& v2){
  e[0] = e[0] / v2.e[0];
  e[1] = e[1] / v2.e[1];
  e[2] = e[2] / v2.e[2];
  return *this;
}

Vec Vec::operator*=(float c){
  *this = *this * c;
  return *this;
}

Vec Vec::operator/=(float c){
  *this = *this / c;
  return *this;
}


float Vec::dot(const Vec& other) const{
  return e[0]*other.e[0] + e[1]*other.e[1] + e[2]*other.e[2];
}

Vec Vec::cross(const Vec& other) const{
  float tempe0 = e[1]*other.e[2] - e[2]*other.e[1];
  float tempe1 = e[2]*other.e[0] - e[0]*other.e[2];
  float tempe2 = e[0]*other.e[1] - e[1]*other.e[0];
  return Vec(tempe0,tempe1,tempe2);
}

float Vec::sqr_mag() const{
  return this->dot(*this);
}
float Vec::magnitude() const{
  return sqrt(this->sqr_mag());
}

Vec Vec::unit() const{
  return Vec((*this) / this->magnitude());
}

Vec Vec::make_unit(){
  *this = this->unit();
  return *this;
}

void Vec::print() const{
  std::cout << this->x() << " " << this->y() << " " << this->z() << std::endl;
}
