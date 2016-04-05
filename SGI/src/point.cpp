#include <vector>
#include "point.hpp"

Point::Point(string name, Coordinate coord) :
		GraphicObject(name, point, vector<Coordinate>()) {
		_coords.push_back(coord);
}