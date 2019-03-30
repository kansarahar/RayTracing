#include "vec.h"
#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "triangle.h"
#include "rectangle.h"
#include "camera.h"
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
//      shoot down -z axis
//      change the list implementations to be cleaner and fix mem leaks


using namespace std;
int main(){
  srand(time(NULL));
  ofstream file;
  vector<Surface> world;
  //Camera cam;
  Camera cam(Vec(0,0,2),Vec(0,1,0),Vec(0,0,-1),4,2,2,400,200);
  file.open("image_perspective.ppm");
  int nx = cam.nx;
  int ny = cam.ny;
  file << "P3\n" << nx << " " << ny << "\n255\n";
  Sphere s(1, Vec(0,0,-5), Vec(0,1,0));
  Vec lower_left_corner = cam.lower_left_corner;
  Vec horizontal_dist = cam.horizontal_dist;
  Vec vertical_dist = cam.vertical_dist;
  Vec light_dir(1,-1,-1);
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

        Vec planePos(lower_left_corner + horizontal_dist*u + vertical_dist*v + Vec(0,0,-cam.d));
        Ray viewRay(Vec(0,0,0), planePos);
        Ray worldRay = cam.toWorld(viewRay);
        bool hits = s.hit(worldRay, 0, 1000);

        if (hits){
          Hit_Record firsthit = worldRay.find_first_hit();
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

}
