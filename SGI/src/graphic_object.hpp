#ifndef SRC_GRAPHICOBJECT_H_
#define SRC_GRAPHICOBJECT_H_

#include <string>
#include <vector>
#include <cmath>
#include <iostream>

#include "matrix.hpp"
#include "window.hpp"

#define PI 3.14159265358979323846
#define DEG2RAD(DEG) (DEG*PI/180.0)

using namespace std;

enum GraphicObjectType {
	point,
	line,
	polygon
};

// ---------------------------

class GraphicObject {
public:
	GraphicObject(string name,  GraphicObjectType type, vector<Coordinate> coords);
	virtual ~GraphicObject();

	string name() const;
	GraphicObjectType type() const;
	vector<Coordinate> coords() const;
	Coordinate centroid() const;

	void normalizeIn(Coordinate windowCenter, double xOffset, double yOffset);

	void translate(VECTOR deslocation);
	void scaleTo(VECTOR factors);
	void rotate(double angle);
	void rotate(double angle, Coordinate anchor);

private:
	void applyTransformation(SQUARE_MATRIX transfMatrix);
	void positionBasedTransformation(SQUARE_MATRIX targetTransformation, Coordinate coord);

protected:
	string _name;
	GraphicObjectType _type;
	vector<Coordinate> _worldCoords;
	vector<Coordinate> _windowCoords;


	SQUARE_MATRIX _buildTranslationMatrix(VECTOR deslocation);
	SQUARE_MATRIX _buildScaleMatrix(double x_factor, double y_factor);
	SQUARE_MATRIX _buildRotationMatrix(double angle);
};

#endif /* SRC_GRAPHICOBJECT_H_ */
