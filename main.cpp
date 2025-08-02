#include <iostream>

#include "color.h"
#include "hittable.h"
#include "ray.h"
#include "sphere.h"
#include "utils.h"
#include "vec3.h"

bool is_debugging = false;

color ray_color(const ray &r) {
    color pixel_color = color(1, 1, 1);
    {
        point3 sphere_center = point3(0, 0, -10);
        float sphere_radius = 3;
        sphere redball = sphere(sphere_center, sphere_radius);
        hit_record rec;
        if (redball.hit(r, 0, 100., rec)) {
            pixel_color = vec_to_color(rec.norm);
        }
    }
    return pixel_color;
}

int main() {
    // Image

    float aspect_ratio = 16. / 9.;
    // int image_width = 1920;
    int image_width = 192;
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    float viewport_width = 2.;
    float viewport_height = viewport_width * (float(image_height) / image_width);
    float focal_length = 1.;
    point3 camera_center = point3(0., 0., 0.);
    vec3 camera_direction = vec3(0, 0, -1.);
    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);
    vec3 pixel_delta_x = viewport_u / image_width;
    vec3 pixel_delta_y = viewport_v / image_height;
    point3 viewport_upperleft = camera_center + focal_length * camera_direction - 0.5 * viewport_u - 0.5 * viewport_v;
    point3 pixel00_loc = viewport_upperleft + 0.5 * pixel_delta_x + 0.5 * pixel_delta_y;

    // Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanning line [" << j << " / " << image_height << "]" << std::flush;
        for (int i = 0; i < image_width; ++i) {
            // if(j == 0 && i == 0){
            //     is_debugging = true;
            // } else {
            //     is_debugging = false;
            // }

            point3 pixel_loc = pixel00_loc + i * pixel_delta_x + j * pixel_delta_y;
            color pixel_color = ray_color(ray(camera_center, pixel_loc - camera_center));
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone!                        " << std::endl;

    return 0;
}