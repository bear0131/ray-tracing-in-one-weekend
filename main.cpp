#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "rtweekend.h"
#include "sphere.h"

int main() {
    // World

    hittable_list world;
    world.add(make_shared<sphere>(point3(1, 0, -10), 3));
    world.add(make_shared<sphere>(point3(-3, -1, -9), 2));
    world.add(make_shared<sphere>(point3(6, -2, -10), 1));
    world.add(make_shared<sphere>(point3(1, -103, -10), 100));

    // Camera
    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 960;

    cam.render(world);

    return 0;
}