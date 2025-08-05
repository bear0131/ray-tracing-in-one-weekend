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
        vec3 reflected = reflect(r_in.direction(), rec.norm);
        vec3 scatter_direction = unit_vector(reflected) + fuzz * random_unit_vector();
        r_scatter = ray(rec.p, scatter_direction);
        return (dot(scatter_direction, rec.norm) > 0);
    }
};

class dielectric : public material {
  private:
    float refractive_indice;

    // Schlick's approximation
    static float reflectance(float cos_theta, float ri) {
        float r0 = (1.0 - ri) / (1.0 + ri);
        r0 = r0 * r0;
        float ret = r0 + (1.0 - r0) * std::pow((1 - cos_theta), 5);
        if (is_debugging) {
            std::cerr << "reflectance = " << ret << std::endl;
        }
        return ret;
    }

  public:
    dielectric(float ri) : refractive_indice(ri) {}
    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &r_scatter) const override {
        attenuation = color(1.0, 1.0, 1.0);

        float ri = rec.front_face ? (1.0 / refractive_indice) : refractive_indice;
        vec3 unit_direction = unit_vector(r_in.direction());
        vec3 scatter_direction;

        float cos_theta = dot(-unit_direction, rec.norm);
        float sin_theta = sqrt(fmax(0.0, 1 - cos_theta * cos_theta));
        bool always_reflects = (ri * sin_theta > 1.0);
        if (always_reflects || random_float() < reflectance(cos_theta, ri)) {
            scatter_direction = reflect(unit_direction, rec.norm);
        } else {
            scatter_direction = refract(unit_direction, rec.norm, ri);
        }

        r_scatter = ray(rec.p, scatter_direction);
        return true;
    }
};

#endif