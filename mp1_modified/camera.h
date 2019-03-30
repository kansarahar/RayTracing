#ifndef CAMERA_H_
#define CAMERA_H_
#include "ray.h"

class Camera{
  public:

    Camera();
    Camera(Vec eye, Vec up, Vec lookAt, float viewPlaneWidth, float viewPlaneHeight, float planeDist, int numx, int numy);

    Vec e;
    Vec u;
    Vec v;
    Vec w;
    float d;

    Vec lower_left_corner; //viewplane will be rectangular symmetric about (0,0)
    int nx;
    int ny;
    Vec horizontal_dist;
    Vec vertical_dist;

    Vec toWorld(Vec viewVector);
    Ray toWorld(Ray viewRay);


  private:
};


#endif
