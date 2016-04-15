#include <vector>
#include "point.hpp"

Point::Point(string name, Coordinate coord) :
		GeometricObject(name, point, {coord} ) {
}

vector<Coordinate> Point::applyClipping() {
	return Clipper::clipPoint(_windowCoords[0]);
}
