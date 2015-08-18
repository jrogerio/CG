/*
 * Point.cpp
 *
 *  Created on: 17 de ago de 2015
 *      Author: plab
 */

#include "Point.h"
#include <vector>


Point::Point(string name, Coordinate coord) :
		GraphicObject(name, GraphicObjectType::POINT, vector<Coordinate>()) {
		_coords.push_back(coord);
}
