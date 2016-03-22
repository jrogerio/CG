/*
 * Polygon.cpp
 *
 *  Created on: 17 de ago de 2015
 *      Author: plab
 */

#include "Polygon.hpp"

Polygon::Polygon(string name, vector<Coordinate> coords) :
		GraphicObject(name, polygon, coords) {
}
