#ifndef SPLINE_INTERPOLATION_GRID_GENERATOR_H_
#define SPLINE_INTERPOLATION_GRID_GENERATOR_H_

#include <vector>

#include "Point.h"

namespace Com_Methods {

// grid generation function
std::vector<Point> Grid(double a, double b, int parts, double ch = 1.0);

}; // Com_Methods

#endif