#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

bool is_debugging = false;

using std::make_shared;
using std::shared_ptr;

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385;
const float eps = 1e-16;

inline float degrees_to_radians(float degrees) { return degrees * pi / 180.; }

std::random_device rd;
std::mt19937 rng(rd());
std::uniform_real_distribution<float> distr(0, 1);

inline float random_float() { return distr(rng); }
inline float random_float(float min, float max) { return min + random_float() * (max - min); }

#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

inline color vec_to_color(vec3 v) { return 0.5 * (v + vec3(1, 1, 1)); }

#endif