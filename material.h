#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material {
  public:
    virtual ~material() = default;
    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &r_scatter) const { return false; }
};

class lambertian : public material {
  private:
    color albedo;

  public:
    lambertian(const color &albedo) : albedo(albedo) {}
    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &r_scatter) const override {
        if (is_debugging) {
            std::cerr << "lambertian scattering " << r_in << std::endl;
        }
        attenuation = albedo;
        vec3 scatter_direction = random_unit_vector() + rec.norm;
        if (scatter_direction.near_zero()) {
            scatter_direction = rec.norm;
        }
        r_scatter = ray(rec.p, scatter_direction);
        return true;
    }
};

class metal : public material {
  private:
    color albedo;
    float fuzz;

  public:
    metal(const color &albedo, float fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}
    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &r_scatter) const override {
        if (is_debugging) {
            std::cerr << "metal scattering " << r_in << std::endl;
        }
        attenuation = albedo;
        vec3 scatter_direction = reflect(r_in.direction(), rec.norm) + fuzz * random_unit_vector();
        r_scatter = ray(rec.p, scatter_direction);
        return (dot(scatter_direction, rec.norm) > 0);
    }
};

#endif