#ifndef HITTABLE_H
#define HITTABLE_H

#include "rtweekend.h"

class hit_record {
  public:
    float t;
    vec3 norm;
    point3 p;
    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = bool(dot(r.direction(), outward_normal) < 0);
        norm = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
  public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, const interval& ray_t, hit_record& rec) const = 0;
};

#endif