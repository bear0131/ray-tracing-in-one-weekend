#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include "interval.h"
#include "vec3.h"

using color = vec3;

void write_color(std::ostream &out, const color &pixel_color) {
    float r = pixel_color.x();
    float g = pixel_color.y();
    float b = pixel_color.z();

    interval idensity(0, 0.999);
    int r_byte = int(255.999 * idensity.clamp(r));
    int g_byte = int(255.999 * idensity.clamp(g));
    int b_byte = int(255.999 * idensity.clamp(b));

    out << r_byte << " " << g_byte << " " << b_byte << "\n";
}

#endif