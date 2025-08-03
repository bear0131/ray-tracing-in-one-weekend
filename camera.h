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
    int samples_per_pixel = 10;
    void render(const hittable& world) {
        initialize();

        std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

        for (int j = 0; j < image_height; ++j) {
            std::clog << "\rScanning line [" << j << " / " << image_height << "]" << std::flush;
            for (int i = 0; i < image_width; ++i) {
                // if (j == image_height / 2 && i == image_width / 2) {
                //     is_debugging = true;
                // } else {
                //     is_debugging = false;
                // }
                color pixel_color = color();
                for (int k = 0; k < samples_per_pixel; ++k) {
                    ray pixel_ray = get_ray(i, j);
                    color sample_color = ray_color(pixel_ray, world);
                    pixel_color += pixel_color_ratio * sample_color;
                }
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
    float pixel_color_ratio;

    void initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_color_ratio = 1. / samples_per_pixel;

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

    ray get_ray(int pixel_x, int pixel_y) {
        vec3 offset = sample_square();
        vec3 ray_target = pixel00_loc + ((pixel_x + offset.x()) * pixel_delta_u) + ((pixel_y + offset.y()) * pixel_delta_v);
        return ray(center, ray_target - center);
    }
    vec3 sample_square() { return vec3(random_float(), random_float(), 0) - vec3(0.5, 0.5, 0.0); }
};

#endif