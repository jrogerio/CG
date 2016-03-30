#include "graphic_object.hpp"

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
	double new_x = 0, new_y = 0;

	for(auto coord : _coords) {
		new_x += coord._x;
		new_y += coord._y;
	}

	new_x = new_x / _coords.size();
	new_y = new_y / _coords.size();

	return Coordinate(new_x, new_y);
}

void GraphicObject::translate(Coordinate deslocation) {
	Matrix<3,3,double> translationMatrix = _buildTranslationMatrix(deslocation);
	applyTransformation(translationMatrix);
}

void GraphicObject::scaleTo(Coordinate factors) {
	Matrix<3,3,double> scaleMatrix = _buildExpansionMatrix(factors._x, factors._y);
	positionBasedTransformation(scaleMatrix, centroid());
}

void GraphicObject::rotate(double angle) {
	Matrix<3,3,double> rotationMatrix = _buildRotationMatrix(angle);
	positionBasedTransformation(rotationMatrix, centroid());
}

void GraphicObject::applyTransformation(Matrix<3,3,double> transfMatrix) {
	Matrix<1,3,double> sourcePosition;
	Matrix<1,3,double> result;

	for (Coordinate &coord : _coords) {
		sourcePosition.setValueOn(0, 0, coord._x);
		sourcePosition.setValueOn(0, 1, coord._y);
		sourcePosition.setValueOn(0, 2, 1);

		result = sourcePosition * transfMatrix;

		coord._x = result.valueOn(0,0);
		coord._y = result.valueOn(0,1);
	}
}

void GraphicObject::positionBasedTransformation(Matrix<3,3,double> targetTransformation, Coordinate coord) {
	Coordinate originDeslocation(-coord._x, -coord._y);

	Matrix<3,3,double> operationMatrix = _buildTranslationMatrix(originDeslocation) *
			targetTransformation *
			_buildTranslationMatrix(originDeslocation.invert());

	applyTransformation(operationMatrix);
}

// Protected functions Homogeneous Coordinates

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
	double radians = DEG2RAD(angle);

	matrix.setValueOn(0, 0, cos(radians));
	matrix.setValueOn(0, 1, -sin(radians));
	matrix.setValueOn(1, 0, sin(radians));
	matrix.setValueOn(1, 1, cos(radians));

	return matrix;
}
