#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "rtweekend.h"

class camera {
  public:
    point3 center = point3(0., 0., 0.);
    vec3 direction = vec3(0, 0, -1.);
    float aspect_ratio = 16. / 9.;
    int image_width = 192;
    float viewport_width = 2.;
    float focal_length = 1.;
    void render(const hittable& world) {
        initialize();

        std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

        for (int j = 0; j < image_height; ++j) {
            std::clog << "\rScanning line [" << j << " / " << image_height << "]" << std::flush;
            for (int i = 0; i < image_width; ++i) {
                if (j == image_height / 2 && i == image_width / 2) {
                    is_debugging = true;
                } else {
                    is_debugging = false;
                }

                point3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                ray pixel_ray = ray(center, pixel_center - center);
                color pixel_color = ray_color(pixel_ray, world);
                write_color(std::cout, pixel_color);
            }
        }

        std::clog << "\rDone!                        " << std::endl;
    }

  private:
    int image_height;
    float viewport_height;
    point3 viewport_upperleft;
    point3 pixel00_loc;
    vec3 viewport_u, viewport_v;
    vec3 pixel_delta_u, pixel_delta_v;

    void initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        viewport_height = viewport_width * (float(image_height) / image_width);
        viewport_u = vec3(viewport_width, 0, 0);
        viewport_v = vec3(0, -viewport_height, 0);
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        viewport_upperleft = center + focal_length * direction - 0.5 * viewport_u - 0.5 * viewport_v;
        pixel00_loc = viewport_upperleft + 0.5 * pixel_delta_u + 0.5 * pixel_delta_v;
    }

    color ray_color(const ray& r, const hittable& world) {
        if (is_debugging) {
            std::cerr << r << std::endl;
        }

        color pixel_color = color(1, 1, 1);
        hit_record rec;
        if (world.hit(r, interval(0, infinity), rec)) {
            pixel_color = vec_to_color(rec.norm);
        }
        return pixel_color;
    }
};

#endif