#pragma once

#include "interval.h"
#include "vec3.h"
#include "camera.h"

#include <array>

using color = vec3;

inline double linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
    {
        return std::sqrt(linear_component);
    }

    return 0;
}

inline std::array<unsigned char, 3> raw_color_bytes(const color& pixel_color)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Apply a linear to gamma transform for gamma 2
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    // Translate the [0,1] norm component values to the byte range [0,255]
    static const interval intensity (0.000, 0.999);
    unsigned char rbyte = int(256 * intensity.clamp(r));
    unsigned char gbyte = int(256 * intensity.clamp(g));
    unsigned char bbyte = int(256 * intensity.clamp(b));

    return {rbyte, gbyte, bbyte};
}

inline void write_color_ppm(std::ostream& out, const color& pixel_color)
{
    auto bytes = raw_color_bytes(pixel_color);
    out << int(bytes[0]) << ' ' << int(bytes[1]) << ' ' << int(bytes[2]) << '\n';
}



