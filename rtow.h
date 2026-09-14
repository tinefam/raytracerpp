#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <numbers>
#include <random>

// Using to better read
using std::make_shared;
using std::shared_ptr;

// Constants
constexpr  double infinity = std::numeric_limits<double>::infinity();
using namespace std::numbers; // For pi

inline double random_double()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max)
{
    // Returns a random real in [min, max)
    return min + (max-min)*random_double();
}

// Utility Functions
inline double degrees_to_radians(const double degrees)
{
    return degrees * pi / 180.0;
}

// Common Headers
#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"