#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "rtweekend.h"

class sphere : public hittable {
  private:
    point3 O;
    float rad;

  public:
    const point3& center() const { return O; }
    float radius() const { return rad; }
    sphere(point3 center, float radius) : O(center), rad(std::fmax(0, radius)) {}
    bool hit(const ray& r, const interval& ray_t, hit_record& rec) const override {
        vec3 loc_rel = r.origin() - center();
        float a = r.direction().length_squared();
        float b = 2. * dot(r.direction(), loc_rel);
        float c = loc_rel.length_squared() - radius() * radius();
        float delta = b * b - 4 * a * c;
        if (delta < 0) {
            return false;
        }
        float sqrtd = std::sqrt(delta);
        float t = (-b - sqrtd) / (2. * a);
        if (!ray_t.surrounds(t)) {
            t = (-b + sqrtd) / (2. * a);
            if (!ray_t.surrounds(t)) {
                return false;
            }
        }

        rec.t = t;
        rec.p = r.at(t);
        vec3 outward_normal = (rec.p - center()) / radius();
        rec.set_face_normal(r, outward_normal);
        return true;
    }
};

#endif