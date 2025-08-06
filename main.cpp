#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "rtweekend.h"
#include "sphere.h"

int main() {
    // World
    hittable_list world;

    shared_ptr<material> ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));
    for (int a = -11; a < 11; ++a) {
        for (int b = -11; b < 11; ++b) {
            float choose_mat = random_float();
            point3 center = point3(a + 0.9 * random_float(), 0.2, b + 0.9 * random_float());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.6) {
                    // diffuse
                    color albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                } else if (choose_mat < 0.9) {
                    // metal
                    color albedo = color::random(0.5, 1);
                    float fuzz = random_float(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                }

                world.add(make_shared<sphere>(center, 0.2, sphere_material));
            }
        }
    }

    shared_ptr<material> material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    shared_ptr<material> material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    shared_ptr<material> material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    // Camera
    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 1920;
    cam.samples_per_pixel = 500;
    cam.max_depth = 50;

    cam.lookfrom = point3(13, 2, 3);
    cam.lookat = point3(0, 0, 0);
    cam.v_up = vec3(0, 1, 0);
    cam.v_fov = 20;

    cam.defocus_angle = 0.6;
    cam.focus_dist = 10.0;

    cam.render(world);

    return 0;
}