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

Matrix<3, 3, double> GraphicObject::_buildTranslationMatrix(Coordinate position) {
	Matrix<3, 3, double> matrix = Matrix<3, 3, double>::buildIdentity();

	matrix.setValueOn(2, 0, position._x);
	matrix.setValueOn(2, 1, position._y);

	return matrix;
}

Matrix<3, 3, double> GraphicObject::_buildExpansionMatrix(double x_factor, double y_factor) {
	Matrix<3, 3, double> matrix = Matrix<3, 3, double>::buildIdentity();

	matrix.setValueOn(0, 0, x_factor);
	matrix.setValueOn(1, 1, y_factor);

	return matrix;
}

Matrix<3, 3, double> GraphicObject::_buildRotationMatrix(double angle) {
	Matrix<3, 3, double> matrix = Matrix<3, 3, double>::buildIdentity();

	matrix.setValueOn(0, 0, cos(angle));
	matrix.setValueOn(0, 1, -sin(angle));
	matrix.setValueOn(1, 1, sin(angle));
	matrix.setValueOn(1, 1, cos(angle));

	return matrix;
}