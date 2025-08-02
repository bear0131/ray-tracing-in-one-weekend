#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr;

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385;

float degrees_to_radians(float degrees) { return degrees * pi / 180.; }

#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

color vec_to_color(vec3 v) { return 0.5 * (v + vec3(1, 1, 1)); }

#endif