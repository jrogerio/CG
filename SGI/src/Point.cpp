/*
 * Point.cpp
 *
 * Author: plab
 */

#include "Point.hpp"
#include <vector>


Point::Point(string name, Coordinate coord) :
		GraphicObject(name, point, vector<Coordinate>()) {
		_coords.push_back(coord);
}
