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

void GraphicObject::normalizeIn(Coordinate windowCenter, double xOffset, double yOffset, SQUARE_MATRIX transformation) {
	int numCoords = _worldCoords.size();

	std::cout << "\n\n window center: (" << windowCenter._x << ", " << windowCenter._y <<")" << std::endl;

	ROW_VECTOR result;

	for (int i = 0; i < numCoords; ++i) {
		result = _worldCoords[i].toHomogenousMatrix() * transformation;
		std::cout << "\n result: (" << result.valueOn(0,0) << ", " << result.valueOn(0,1) <<")" << std::endl;

		_windowCoords[i]._x = ( result.valueOn(0,0) - windowCenter._x ) / (xOffset);
		_windowCoords[i]._y = ( result.valueOn(0,1) - windowCenter._y ) / (yOffset);
	}
}

void GraphicObject::translate(VECTOR deslocation) {
	SQUARE_MATRIX translationMatrix = _buildTranslationMatrix(deslocation);
	applyTransformation(_worldCoords, translationMatrix);
}

void GraphicObject::scaleTo(VECTOR factors) {
	SQUARE_MATRIX scaleMatrix = _buildScaleMatrix(factors._x, factors._y);
	positionBasedTransformation(_worldCoords, scaleMatrix, centroid());
}

void GraphicObject::rotate(double radians) {
	SQUARE_MATRIX rotationMatrix = _buildRotationMatrix(radians);
	positionBasedTransformation(_worldCoords, rotationMatrix, centroid());
}

void GraphicObject::rotate(double radians, Coordinate anchor) {
	SQUARE_MATRIX rotationMatrix = _buildRotationMatrix(radians);
	positionBasedTransformation(_worldCoords, rotationMatrix, anchor);
}

void GraphicObject::applyTransformation(vector<Coordinate>& coordSystem, SQUARE_MATRIX transfMatrix) {
	ROW_VECTOR sourcePosition;
	ROW_VECTOR result;

	int numCoords = _worldCoords.size();

	for (int i = 0; i < numCoords; ++i) {
		sourcePosition = coordSystem[i].toHomogenousMatrix();
		result = sourcePosition * transfMatrix;

		coordSystem[i]._x = result.valueOn(0,0);
		coordSystem[i]._y = result.valueOn(0,1);
	}

	for (Coordinate &coord : _worldCoords) {
	}
}

void GraphicObject::positionBasedTransformation(vector<Coordinate>& coordSystem, SQUARE_MATRIX targetTransformation, Coordinate coord) {
	Coordinate originDeslocation(-coord._x, -coord._y);

	SQUARE_MATRIX operationMatrix = _buildTranslationMatrix(originDeslocation) *
			targetTransformation *
			_buildTranslationMatrix(originDeslocation.negate());

	applyTransformation(coordSystem, operationMatrix);
}
