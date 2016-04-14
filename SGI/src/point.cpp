#include <vector>
#include "point.hpp"

Point::Point(string name, Coordinate coord) :
		GeometricObject(name, point, {coord} ) {
}

void Point::applyClipping() {
	bool outOfRange = fabs(_windowCoords[0]._x) > 1 || fabs(_windowCoords[0]._y) > 1;

	if (outOfRange)
		_windowCoords.pop_back();
}
