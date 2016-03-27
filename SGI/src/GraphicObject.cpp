/*
 * GraphicObject.cpp
 *
 * Author: plab
 */

#include "GraphicObject.hpp"

GraphicObject::GraphicObject(string name, GraphicObjectType type,
		vector<Coordinate> coords) :
		_name(name), _type(type), _coords(coords) {
}

GraphicObject::~GraphicObject() {
}

string GraphicObject::name() const {
	return _name;
}

GraphicObjectType GraphicObject::type() const {
	return _type;
}

vector<Coordinate> GraphicObject::coords() const {
	return _coords;
}

Coordinate GraphicObject::centroid() const {
	double new_x, new_y;

	for(auto &coord : _coords) {
		new_x += coord._x;
		new_y += coord._y;
	}

	new_x = new_x / _coords.size();
	new_y = new_y / _coords.size();

	return Coordinate(new_x, new_y);
}
