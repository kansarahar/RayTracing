#include "camera.h"

Camera::Camera(){
  e = Vec(0,0,0);
  w = Vec(0,0,1);
  u = Vec(1,0,0);
  v = Vec(0,1,0);
  d = 2;

  lower_left_corner = Vec(-2,-1,0);
  nx = 200;
  ny = 100;

  horizontal_dist = Vec(-2*lower_left_corner.x(),0,0);
  vertical_dist = Vec(0, -2*lower_left_corner.y(),0);
}

Camera::Camera(Vec eye, Vec up, Vec lookAt, float viewPlaneWidth, float viewPlaneHeight, float planeDist, int numx, int numy){
  e = eye;
  w = (eye-lookAt).make_unit();
  u = (up.cross(w)).make_unit();
  v = (w.cross(u)).make_unit();
  d = planeDist;

  lower_left_corner = Vec(viewPlaneWidth/(-2), viewPlaneHeight/(-2), 0);
  nx = numx;
  ny = numy;

  horizontal_dist = Vec(viewPlaneWidth,0,0);
  vertical_dist = Vec(0,viewPlaneHeight,0);
}

Vec Camera::toWorld(Vec viewVector){
  Vec wx = u*viewVector.x();
  Vec wy = v*viewVector.y();
  Vec wz = w*viewVector.z();
  return (wx + wy + wz);
}

Ray Camera::toWorld(Ray viewRay){
  return Ray(e + toWorld(viewRay.origin()), toWorld(viewRay.direction()));
}
