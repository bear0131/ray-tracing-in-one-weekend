#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : hittable {
  private:
    point3 O;
    float rad;

  public:
    const point3& center() const { return O; }
    float radius() const { return rad; }
    sphere(point3 center, float radius) : O(center), rad(std::fmax(0, radius)) {}
    bool hit(const ray& r, float ray_tmin, float ray_tmax, hit_record& rec) const {
        vec3 loc_rel = r.origin() - center();
        float a = r.direction().length_squared();
        float b = 2. * dot(r.direction(), loc_rel);
        float c = loc_rel.length_squared() - radius() * radius();
        float delta = b * b - 4 * a * c;
        if (delta < 0) {
            return false;
        }
        float t = (-b - std::sqrt(delta)) / (2. * a);
        if (t < ray_tmin || t > ray_tmax) {
            return false;
        }

        rec.t = t;
        rec.p = r.at(t);
        rec.norm = (rec.p - center()) / radius();
        return true;
    }
};

#endif