#ifndef UTILS_H
#define UTILS_H

#include <cmath>

#include "vec3.h"
#include "color.h"
#include "ray.h"

color vec_to_color(vec3 v){
    return 0.5 * (v + vec3(1, 1, 1));
}

#endif