#include "graphic_object.hpp"

GraphicObject::GraphicObject(string name, GraphicObjectType type,
		vector<Coordinate> coords) :
		_name(name), _type(type), _worldCoords(coords) {
			for(Coordinate coord : coords) {
				_windowCoords.push_back( Coordinate() );
			}
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
	return _windowCoords;
}

Coordinate GraphicObject::centroid() const {
	double new_x = 0, new_y = 0;

	for(auto coord : _worldCoords) {
		new_x += coord._x;
		new_y += coord._y;
	}

	new_x = new_x / _worldCoords.size();
	new_y = new_y / _worldCoords.size();

	return Coordinate(new_x, new_y);
}

void GraphicObject::normalizeIn(Coordinate windowCenter, double xOffset, double yOffset) {
	int numCoords = _worldCoords.size();
	uint size = _windowCoords.size();

	for (int i = 0; i < numCoords; ++i) {
		_windowCoords[i]._x = ( _worldCoords[i]._x - windowCenter._x ) / (xOffset);
		_windowCoords[i]._y = ( _worldCoords[i]._y - windowCenter._y ) / (yOffset);
	}
}

void GraphicObject::translate(VECTOR deslocation) {
	SQUARE_MATRIX translationMatrix = _buildTranslationMatrix(deslocation);
	applyTransformation(translationMatrix);
}

void GraphicObject::scaleTo(VECTOR factors) {
	SQUARE_MATRIX scaleMatrix = _buildScaleMatrix(factors._x, factors._y);
	positionBasedTransformation(scaleMatrix, centroid());
}

void GraphicObject::rotate(double angle) {
	SQUARE_MATRIX rotationMatrix = _buildRotationMatrix(angle);
	positionBasedTransformation(rotationMatrix, centroid());
}

void GraphicObject::rotate(double angle, Coordinate anchor) {
	SQUARE_MATRIX rotationMatrix = _buildRotationMatrix(angle);
	positionBasedTransformation(rotationMatrix, anchor);
}

void GraphicObject::applyTransformation(SQUARE_MATRIX transfMatrix) {
	ROW_VECTOR sourcePosition;
	ROW_VECTOR result;

	for (Coordinate &coord : _worldCoords) {
		sourcePosition = coord.toHomogenousMatrix();
		result = sourcePosition * transfMatrix;

		coord._x = result.valueOn(0,0);
		coord._y = result.valueOn(0,1);
	}
}

void GraphicObject::positionBasedTransformation(SQUARE_MATRIX targetTransformation, Coordinate coord) {
	Coordinate originDeslocation(-coord._x, -coord._y);

	SQUARE_MATRIX operationMatrix = _buildTranslationMatrix(originDeslocation) *
			targetTransformation *
			_buildTranslationMatrix(originDeslocation.negate());

	applyTransformation(operationMatrix);
}

// Protected functions Homogeneous Coordinates

SQUARE_MATRIX GraphicObject::_buildTranslationMatrix(VECTOR deslocation) {
	SQUARE_MATRIX matrix = SQUARE_MATRIX::buildIdentity();

	matrix.setValueOn(2, 0, deslocation._x);
	matrix.setValueOn(2, 1, deslocation._y);

	return matrix;
}

SQUARE_MATRIX GraphicObject::_buildScaleMatrix(double x_factor, double y_factor) {
	SQUARE_MATRIX matrix = SQUARE_MATRIX::buildIdentity();

	matrix.setValueOn(0, 0, x_factor);
	matrix.setValueOn(1, 1, y_factor);

	return matrix;
}

SQUARE_MATRIX GraphicObject::_buildRotationMatrix(double angle) {
	SQUARE_MATRIX matrix = SQUARE_MATRIX::buildIdentity();
	double radians = DEG2RAD(angle);

	matrix.setValueOn(0, 0, cos(radians));
	matrix.setValueOn(0, 1, sin(radians));
	matrix.setValueOn(1, 0, -sin(radians));
	matrix.setValueOn(1, 1, cos(radians));

	return matrix;
}
