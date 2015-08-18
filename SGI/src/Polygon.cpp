/*
 * Polygon.cpp
 *
 *  Created on: 17 de ago de 2015
 *      Author: plab
 */

#include "Polygon.h"

Polygon::Polygon(string name, vector<Coordinate> coords) :
		GraphicObject(name, GraphicObjectType::POLYGON, coords) {
}
