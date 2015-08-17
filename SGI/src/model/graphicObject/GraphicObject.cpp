/*
 * GraphicObject.cpp
 *
 *  Created on: 17 de ago de 2015
 *      Author: plab
 */

#include "GraphicObject.h"

GraphicObject::GraphicObject(string name, list<Coordinate> coords): _name(name), _coords(coords) {
	// TODO Auto-generated constructor stub

}

GraphicObject::~GraphicObject() {
	// TODO Auto-generated destructor stub
}

string GraphicObject::name()
{
	return _name;
}

string GraphicObject::type()
{
	return _type;
}

list<Coordinate> GraphicObject::coords()
{
	return _coords;
}
