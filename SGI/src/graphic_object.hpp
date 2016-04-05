#ifndef SRC_GRAPHICOBJECT_H_
#define SRC_GRAPHICOBJECT_H_

#include <string>
#include <vector>
#include <cmath>
#include "matrix.hpp"

#define SQUARE_MATRIX Matrix<3,3>
#define ROW_VECTOR Matrix<1,3>

#define PI 3.14159265358979323846
#define DEG2RAD(DEG) (DEG*PI/180.0)

#define VECTOR Coordinate

using namespace std;

struct Coordinate {

	Coordinate(double x, double y): _x(x), _y(y) {}

public:
	double _x,_y;

	Coordinate negate(){ return Coordinate(-_x, -_y); }
	ROW_VECTOR toHomogenousMatrix(){
		ROW_VECTOR homogeneousMatrix;
		homogeneousMatrix.setValueOn(0, 0, _x);
		homogeneousMatrix.setValueOn(0, 1, _y);
		homogeneousMatrix.setValueOn(0, 2, 1);

		return homogeneousMatrix;
	}
};

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

	void translate(VECTOR deslocation);
	void scaleTo(VECTOR factors);
	void rotate(double angle);
	void rotate(double angle, Coordinate anchor);
	void applyTransformation(SQUARE_MATRIX transfMatrix);

protected:
	string _name;
	GraphicObjectType _type;
	vector<Coordinate> _coords;

	void positionBasedTransformation(SQUARE_MATRIX targetTransformation, Coordinate coord);

	SQUARE_MATRIX _buildTranslationMatrix(VECTOR deslocation);
	SQUARE_MATRIX _buildScaleMatrix(double x_factor, double y_factor);
	SQUARE_MATRIX _buildRotationMatrix(double angle);
};

#endif /* SRC_GRAPHICOBJECT_H_ */
