#include "ray.h"
#include "sdltemplate.h"
#include "vec3.h"
#include <iostream>

vec3 colour(const ray& r) {
  vec3 unitDir = unit_vector(r.direction());
  double t = 0.5 * (unitDir.y() + 1.0);
  return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main() {

  // 4:2 Aspect Ratio
  int image_width = 800;
  int image_height = 400;

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

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  sdltemplate::sdl("Ray Tracer", image_width, image_height);
  sdltemplate::loop();

  for (int j = 0; j < image_height; j++) {
    for (int i = 0; i < image_width; i++) {
      double u = double(i) / double(image_width);
      double v = double(j) / double(image_height);
      ray r = ray(origin, lowerLeftCorner + u * horizontal + v * vertical);
      // vec3 col(double(i) / (image_width - 1), double(j) / (image_height - 1),
      //  0.0);
      vec3 col = colour(r);
      int ir = int(255.999 * col.x());
      int ig = int(255.999 * col.y());
      int ib = int(255.999 * col.z());

      std::cout << ir << ' ' << ig << ' ' << ib << '\n';
      sdltemplate::setDrawColor(sdltemplate::createColor(ir, ig, ib, 255));
      sdltemplate::drawPoint(i, j);
    }
  }

  while (sdltemplate::running) {
    sdltemplate::loop();
  }
}