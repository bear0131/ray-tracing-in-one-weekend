#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "vec3.h"

class hit_record {
  public:
    float t;
    vec3 norm;
    point3 p;
};

class hittable {
  public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, float ray_tmin, float ray_tmax, hit_record& h) const = 0;
};

#endif