#include <iostream>

#include "grid_generator.h"

namespace Com_Methods {

std::vector<Point> Grid(double a, double b, int parts, double ch) {

	std::vector<Point> result;

	double x = a;
	result.push_back(Point(x, 0.0, 0.0));

	double s = 1;
	for (int i = 1; i < parts; i++)
		s += pow(ch, i);
	double step = (b - a) / s;

	for (int i = 0; i < parts; i++)
		result.push_back(Point(x += step * pow(ch, i), 0.0, 0.0));

	return result;
};

}; // namespace Com_Methods