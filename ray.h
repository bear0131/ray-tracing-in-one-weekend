#ifndef RAY_H
#define RAY_H

#include <iostream>

#include "vec3.h"

class ray {
  private:
    point3 orig;
    vec3 dir;

  public:
    ray() = default;
    ray(point3 origin, vec3 direction) : orig(origin), dir(direction) {}

    const point3& origin() const { return orig; }
    const vec3& direction() const { return dir; }

    point3 at(float t) const { return orig + t * dir; }
};

std::ostream& operator<<(std::ostream& o, const ray& r) { return o << r.origin() << " + " << r.direction() << "t"; }

#endif