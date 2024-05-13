#ifndef SCENE_H
#define SCENE_H

#include "ray.h"
#include "vec3.h"
#include <cmath>

// Function to determine if a ray hits a sphere
double hitSphere(const vec3& centre, double radius, const ray& r) {
  vec3 oc = r.origin() - centre;
  double a = dot(r.direction(), r.direction());
  double b = 2.0 * dot(oc, r.direction());
  double c = dot(oc, oc) - radius * radius;
  double discrimant = b * b - 4 * a * c;
  if (discrimant < 0) {
    return -1.0;
  } else {
    return (-b - sqrt(discrimant)) / (2.0 * a);
  }
}

// Function to compute color at a ray intersection
vec3 colour(const ray& r, const vec3& sphereCentre, double sphere_radius) {
  double t = hitSphere(sphereCentre, sphere_radius, r);
  if (t > 0.0) {
    // Now if the ray hits the sphere, we will compute the normalised vector
    // from the sphere's centre to hit the point on the sphere's surface
    vec3 N = unitVector(r.at(t) - sphereCentre);
    return 0.5 * vec3(N.x() + 1, N.y() + 1, N.z() + 1);
  }
  // Converts the ray/vector into a unit vector
  vec3 unitDirection = unitVector(r.direction());
  // t is a value between 0 and 1, where 0 corresponds to a ray poitning
  // downward, and 1 being upward
  t = 0.5 * (unitDirection.y() + 1.0);
  /*
   * 1.0, 1.0, 1.0 is white
   * 0.5, 0.7, 1.0 is blue
   *
   * Hence, as we multiple white by (1.0 - t), upwards will be blue, downwards
   * will be white
   */
  return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

#endif // SCENE_H
