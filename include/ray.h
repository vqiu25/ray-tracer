#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {

private:
  point3 orig;
  vec3 dir;

public:
  // Constructors
  ray() {}
  ray(const point3& origin, const vec3& direction)
      : orig(origin), dir(direction) {}

  // Getters
  const point3& origin() const { return orig; }
  const vec3& direction() const { return dir; }

  // Computes a point along the ray at distance t
  point3 at(double t) const { return orig + t * dir; }
};

#endif
