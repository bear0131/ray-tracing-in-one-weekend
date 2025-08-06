#ifndef CAMERA_H
#define CAMERA_H

#include <sysinfoapi.h>

#include <cassert>

#include "hittable.h"
#include "material.h"
#include "rtweekend.h"

class camera {
  public:
    point3 lookfrom = point3(0.0, 0.0, 0.0);
    point3 lookat = point3(0.0, 0.0, -1.0);
    vec3 v_up = vec3(0.0, 1.0, 0.0);
    float v_fov = 30;

    float aspect_ratio = 16. / 9.;
    int image_width = 192;
    int samples_per_pixel = 10;
    int max_depth = 10;

    float defocus_angle = 0;
    float focus_dist = 10;

    void render(const hittable& world) {
        initialize();

        float start_time = GetTickCount();

        std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

        for (int j = 0; j < image_height; ++j) {
            std::clog << "\rScanning line [" << j << " / " << image_height << "]" << std::flush;
            for (int i = 0; i < image_width; ++i) {
                // if (j == image_height / 2 && i == 0) {
                //     is_debugging = true;
                // } else {
                //     is_debugging = false;
                // }
                color pixel_color = color();
                for (int k = 0; k < samples_per_pixel; ++k) {
                    ray pixel_ray = get_ray(i, j);
                    color sample_color = ray_color(pixel_ray, max_depth, world);
                    pixel_color += pixel_color_ratio * sample_color;
                }
                write_color(std::cout, pixel_color);
            }
        }

        float end_time = GetTickCount();

        std::clog << "\rDone in " << 0.001 * (end_time - start_time) << "s              " << std::endl;
    }

  private:
    int image_height;
    float viewport_width;
    float viewport_height;
    point3 viewport_upperleft;
    point3 pixel00_loc;
    vec3 viewport_u, viewport_v;
    vec3 pixel_delta_u, pixel_delta_v;
    float pixel_color_ratio;
    vec3 u, v, w;  // right, up, back
    vec3 defocus_disk_u, defocus_disk_v;

    void initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_color_ratio = 1. / samples_per_pixel;

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(v_up, w));
        v = cross(w, u);
        assert(fabs(dot(u, v)) < 1e-5 && fabs(dot(v, w)) < 1e-5 && fabs(dot(w, u)) < 1e-5);

        float theta = degrees_to_radians(v_fov);
        viewport_height = 2. * focus_dist * std::tan(theta * 0.5);
        viewport_width = viewport_height * (float(image_width) / image_height);

        float defocus_radius = std::tan(degrees_to_radians(defocus_angle * 0.5));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;

        viewport_u = viewport_width * u;
        viewport_v = -viewport_height * v;
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;
        viewport_upperleft = lookfrom - focus_dist * w - 0.5 * viewport_u - 0.5 * viewport_v;
        pixel00_loc = viewport_upperleft + 0.5 * pixel_delta_u + 0.5 * pixel_delta_v;
    }

    color ray_color(const ray& r, int depth, const hittable& world) {
        if (is_debugging) {
            std::cerr << r << std::endl;
        }

        if (depth <= 0) {
            return color(0, 0, 0);
        }
        hit_record rec;
        if (world.hit(r, interval(0.001, infinity), rec)) {
            if (is_debugging) {
                std::cerr << "hit! " << r << " " << rec.mat << std::endl;
            }
            color attenuation;
            ray r_out;
            if (rec.mat->scatter(r, rec, attenuation, r_out)) {
                return attenuation * ray_color(r_out, depth - 1, world);
            } else {
                return color(0, 0, 0);
            }
        }

        vec3 unit_direction = unit_vector(r.direction());
        float a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }

    ray get_ray(int pixel_x, int pixel_y) {
        vec3 offset = sample_square();
        point3 pixel_sample = pixel00_loc + ((pixel_x + offset.x()) * pixel_delta_u) + ((pixel_y + offset.y()) * pixel_delta_v);
        point3 ray_origin = (defocus_angle <= 0) ? lookfrom : defocus_disk_sample();
        return ray(ray_origin, pixel_sample - ray_origin);
    }
    vec3 sample_square() { return vec3(random_float(), random_float(), 0) - vec3(0.5, 0.5, 0.0); }
    vec3 defocus_disk_sample() {
        vec3 p = random_on_unit_disk();
        return lookfrom + p[0] * defocus_disk_u + p[1] * defocus_disk_v;
    }
};

#endif