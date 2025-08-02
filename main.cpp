#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "rtweekend.h"
#include "sphere.h"

int main() {
    // World

    hittable_list world;
    world.add(make_shared<sphere>(point3(1, 0, -10), 4));
    world.add(make_shared<sphere>(point3(-2, 0, -3), 2));

    // Camera
    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 192;

    cam.render(world);

    return 0;
}