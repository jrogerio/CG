/*
 * Line.cpp
 *
 *  Created on: 17 de ago de 2015
 *      Author: plab
 */

#include "Line.h"

Line::Line(string name, Coordinate first, Coordinate second) :
	GraphicObject(name, line, vector<Coordinate>()) {
		_coords.push_back(first);
		_coords.push_back(second);
}

