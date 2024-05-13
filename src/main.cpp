#include "ray.h"
#include "sdltemplate.h"
#include "vec3.h"
#include <iostream>

double hit_sphere(const vec3 centre, double radius, const ray& r) {
  vec3 oc = r.origin() - centre;
  double a = dot(r.direction(), r.direction());
  double b = 2.0 * dot(oc, r.direction());
  double c = dot(oc, oc) - radius * radius;
  float discrimant = b * b - 4 * a * c;
  if (discrimant < 0) {
    return -1;
  } else {
    return (-b - sqrt(discrimant)) / (2.0 * a);
  }
}

vec3 sphere;
double sphere_radius;

vec3 colour(const ray& r) {
  double t = hit_sphere(sphere, sphere_radius, r);
  if (t > 0.0) {
    // Now if the ray hits the sphere, we will compute the normalised vector
    // from the sphere's centre to hit the point on the sphere's surface
    vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
    return 0.5 * vec3(N.x() + 1, N.y() + 1, N.z() + 1);
  }

  // Converts the ray/vector into a unit vector
  vec3 unitDir = unit_vector(r.direction());
  // t is a value between 0 and 1, where 0 corresponds to a ray poitning
  // downward, and 1 being upward
  t = 0.5 * (unitDir.y() + 1.0);
  /*
   * 1.0, 1.0, 1.0 is white
   * 0.5, 0.7, 1.0 is blue
   *
   * Hence, as we multiple white by (1.0 - t), upwards will be blue, downwards
   * will be white
   */
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

  // Create a Sphere
  sphere = vec3(0, 0, -1);
  sphere_radius = 0.5;

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  sdltemplate::sdl("Ray Tracer", image_width, image_height);
  sdltemplate::loop();

  for (int j = 0; j < image_height; j++) {
    for (int i = 0; i < image_width; i++) {
      double u = double(i) / double(image_width);
      double v = double(j) / double(image_height);

      // Identify where to project ray to draw
      ray r = ray(origin, lowerLeftCorner + u * horizontal + v * vertical);
      // Set the colour of where the ray is pointing
      vec3 col = colour(r);

      int ir = int(255.999 * col.x());
      int ig = int(255.999 * col.y());
      int ib = int(255.999 * col.z());

      // std::cout << ir << ' ' << ig << ' ' << ib << '\n';
      sdltemplate::setDrawColor(sdltemplate::createColor(ir, ig, ib, 255));
      sdltemplate::drawPoint(i, image_height - j);
    }
  }

  while (sdltemplate::running) {
    sdltemplate::loop();
  }
}
