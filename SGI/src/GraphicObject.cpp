/*
 * GraphicObject.cpp
 *
 *  Created on: 17 de ago de 2015
 *      Author: plab
 */

#include "GraphicObject.h"

GraphicObject::GraphicObject(string name, GraphicObjectType type,
		vector<Coordinate> coords) :
		_name(name), _type(type), _coords(coords) {
}

GraphicObject::~GraphicObject() {
}

string GraphicObject::name() {
	return _name;
}

GraphicObjectType GraphicObject::type() {
	return _type;
}

vector<Coordinate> GraphicObject::coords() {
	return _coords;
}
