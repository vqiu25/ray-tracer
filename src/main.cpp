#include "ray.h"
#include "scene.h"
#include "sdltemplate.h"
#include "vec3.h"
#include <iostream>

int main() {

  // 4:2 Aspect Ratio
  int imageWidth = 800;
  int imageHeight = 400;

  /*
  Visual Representation:
  * Camera at (0, 0, 0)

    (-2, 1, 1)  .-------.  (2, 1, 1)
                |       |
                |       |
  (-2, -1, -1)  .-------.  (2, -1, -1)

  */

  vec3 lowerLeftCorner = vec3(-2.0, -1.0, -1.0);
  vec3 horizontal = vec3(4.0, 0.0, 0.0);
  vec3 vertical = vec3(0.0, 2.0, 0.0);
  vec3 origin = vec3(0.0, 0.0, 0.0);
  vec3 sphereCentre(0, 0, -1);
  double sphere_radius = 0.5;

  std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
  sdltemplate::sdl("Ray Tracer", imageWidth, imageHeight);
  sdltemplate::loop();

  for (int j = 0; j < imageHeight; j++) {
    for (int i = 0; i < imageWidth; i++) {
      double u = double(i) / double(imageWidth);
      double v = double(j) / double(imageHeight);
      ray r(origin, lowerLeftCorner + u * horizontal + v * vertical);
      vec3 col = colour(r, sphereCentre, sphere_radius);
      int ir = int(255.999 * col.x());
      int ig = int(255.999 * col.y());
      int ib = int(255.999 * col.z());

      sdltemplate::setDrawColor(sdltemplate::createColor(ir, ig, ib, 255));
      sdltemplate::drawPoint(i, imageHeight - j);
    }
  }

  while (sdltemplate::running) {
    sdltemplate::loop();
  }
}
