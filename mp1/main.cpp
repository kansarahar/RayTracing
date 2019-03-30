#include "vec.h"
#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "triangle.h"
#include "rectangle.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

//much of this code was taken from the Ray Tracing in One Weekend
//by Peter Shirley
//namely most of ray.h/cpp and sphere.h/cpp

//todo: make it so that there is no error if three points do not form a triangle;
//      clean up the code
//      change the list implementations to be cleaner and fix mem leaks


using namespace std;
int main(){
  srand(time(NULL));
  ofstream file;
  file.open("image_orthographic.ppm");
  int nx = 400;
  int ny = 200;
  float zdist = 3;
  file << "P3\n" << nx << " " << ny << "\n255\n";
  Triangle tr(Vec(0,-0.5,2), Vec(-2.5,-1.25,1.5), Vec(1,1.5,4), Vec(1,0,0));
  Sphere s(1, Vec(-1.5,0,3), Vec(0,1,0));
  Rectangle rect1(Vec(-0.5,-0.5,zdist), Vec(-0.5,1.5,zdist), Vec(0.5,0,zdist+0.5), Vec(0,0,1));
  Rectangle rect2(Vec(-1,0,zdist+1), Vec(-1,2,zdist+1), Vec(-0.5,-0.5,zdist), Vec(0,0,1));
  Rectangle rect3(Vec(-0.5,1.5,zdist), Vec(-1,2,zdist+1), Vec(0.5,2,zdist+0.5), Vec(0,0,1));
  Vec lower_left_corner(-2,-1,0);
  Vec origin(0,0,0);
  Vec horizontal_dist(4,0,0);
  Vec vertical_dist(0,2,0);
  Vec light_dir(1,-1,1);
  light_dir.make_unit();
  Vec light_color(1,1,1);
  float red = 0;
  float green = 0;
  float blue = 0;


  for (int j = ny-1; j >= 0; j--){
    for (int i = 0; i < nx; i++){
      red = 0;
      green = 0;
      blue = 0;
      for (int k = 0; k < 25; k++){
        float randintu = float(rand() % 10000);
        float randintv = float(rand() % 10000);
        float randu = randintu/10000;
        float randv = randintv/10000;
        float u = (float(i)+randu)/float(nx);
        float v = (float(j)+randv)/float(ny);

        Vec planePos(lower_left_corner + horizontal_dist*u + vertical_dist*v);
        Vec rayPos = Vec(0,0,1);
        Ray ray(planePos, rayPos);
        bool hits = s.hit(ray, 0, 1000);
        bool hitt = tr.hit(ray, 0, 1000);
        bool hitr1 = rect1.hit(ray, 0, 1000);
        bool hitr2 = rect2.hit(ray, 0, 1000);
        bool hitr3 = rect3.hit(ray, 0, 1000);
        if (hitr1 || hitr2 || hitr3 || hits || hitt){
          const Hit_Record& firsthit = ray.hrl.find_first_hit();
          Vec norm = firsthit.normal;
          norm.make_unit();
          Vec newColor = (firsthit.color * light_color) * norm.dot(light_dir) * -1;
          if (norm.dot(light_dir) >= 0){newColor = Vec(0,0,0);}
          red = red+newColor[0];
          green = green+newColor[1];
          blue = blue+newColor[2];
        }
      }
      Vec illumination(red, green, blue);
      illumination = illumination/25.0;
      illumination = illumination*255;
      file << int(illumination.r()) << " " << int(illumination.g()) << " " << int(illumination.b()) << "\n";
    }
  }
  file.close();





  ofstream file2;
  file2.open("image_perspective.ppm");
  file2 << "P3\n" << nx << " " << ny << "\n255\n";


  for (int j = ny-1; j >= 0; j--){
    for (int i = 0; i < nx; i++){
      red = 0;
      green = 0;
      blue = 0;
      for (int k = 0; k < 25; k++){
        float randintu = float(rand() % 10000);
        float randintv = float(rand() % 10000);
        float randu = randintu/10000;
        float randv = randintv/10000;
        float u = (float(i)+randu)/float(nx);
        float v = (float(j)+randv)/float(ny);

        Vec planePos(lower_left_corner + horizontal_dist*u + vertical_dist*v);
        Vec camera(0,0,-2);
        Vec rayPos = planePos-camera;
        Ray ray(planePos, rayPos);
        bool hits = s.hit(ray, 0, 1000);
        bool hitt = tr.hit(ray, 0, 1000);
        bool hitr1 = rect1.hit(ray, 0, 1000);
        bool hitr2 = rect2.hit(ray, 0, 1000);
        bool hitr3 = rect3.hit(ray, 0, 1000);
        if (hitr1 || hitr2 || hitr3 || hits || hitt){
          const Hit_Record& firsthit = ray.hrl.find_first_hit();
          Vec norm = firsthit.normal;
          norm.make_unit();
          Vec newColor = (firsthit.color * light_color) * norm.dot(light_dir) * -1;
          if (norm.dot(light_dir) >= 0){newColor = Vec(0,0,0);}
          red = red+newColor[0];
          green = green+newColor[1];
          blue = blue+newColor[2];
        }
      }
      Vec illumination(red, green, blue);
      illumination = illumination/25.0;
      illumination = illumination*255;
      file2 << int(illumination.r()) << " " << int(illumination.g()) << " " << int(illumination.b()) << "\n";
    }
  }
  file2.close();

}
