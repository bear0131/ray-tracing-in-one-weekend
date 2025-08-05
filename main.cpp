#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "rtweekend.h"
#include "sphere.h"

int main() {
    // Materials
    shared_ptr<material> material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    shared_ptr<material> material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    shared_ptr<material> material_left = make_shared<dielectric>(1.5);
    shared_ptr<material> material_bubble = make_shared<dielectric>(1.0 / 1.5);
    // shared_ptr<material> material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);
    shared_ptr<material> material_right = make_shared<metal>(color(0.6, 0.6, 0.6), 0.0);

    // Hittables
    hittable_list world;
    world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.4, material_bubble));
    world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

    // Camera
    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 960;
    cam.samples_per_pixel = 50;
    cam.max_depth = 50;
    cam.center = point3(0, 0, 0);
    cam.direction = unit_vector(vec3(0, 0, -1));

    cam.render(world);

    return 0;
}