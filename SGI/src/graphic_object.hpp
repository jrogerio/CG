#ifndef SRC_GRAPHICOBJECT_H_
#define SRC_GRAPHICOBJECT_H_

#include <string>
#include <vector>
#include <cmath>
#include "matrix.hpp"

#define PI 3.14159265358979323846
#define DEG2RAD(DEG) (DEG*PI/180.0)

#define Vector Coordinate

using namespace std;

struct Coordinate {

	Coordinate(double x, double y): _x(x), _y(y) {}

public:
	double _x,_y;

	Coordinate negate(){ return Coordinate(-_x, -_y); }
	Matrix<1,3> toHomogenousMatrix(){
		Matrix<1,3> homogeneousMatrix;
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

	void translate(Vector deslocation);
	void scaleTo(Vector factors);
	void rotate(double angle);
	void applyTransformation(Matrix<3,3> transfMatrix);

protected:
	string _name;
	GraphicObjectType _type;
	vector<Coordinate> _coords;

	void positionBasedTransformation(Matrix<3,3> targetTransformation, Coordinate coord);

	Matrix<3, 3> _buildTranslationMatrix(Vector deslocation);
	Matrix<3, 3> _buildScaleMatrix(double x_factor, double y_factor);
	Matrix<3, 3> _buildRotationMatrix(double angle);
};

#endif /* SRC_GRAPHICOBJECT_H_ */
