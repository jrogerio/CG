#ifndef SRC_GRAPHICOBJECT_H_
#define SRC_GRAPHICOBJECT_H_

#include <string>
#include <vector>
#include <cmath>
#include "matrix.hpp"

#define PI 3.14159265358979323846
#define DEG2RAD(DEG) (DEG*PI/180.0)

using namespace std;

struct Coordinate {

	Coordinate(double x, double y): _x(x), _y(y) {}

public:
	double _x,_y;

	Coordinate invert(){ return Coordinate(-_x, -_y); }
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

	void translate(Coordinate deslocation);
	void scaleTo(Coordinate factors);
	void rotate(double angle);
	void applyTransformation(Matrix<3,3,double> transfMatrix);

protected:
	string _name;
	GraphicObjectType _type;
	vector<Coordinate> _coords;

	void positionBasedTransformation(Matrix<3,3,double> targetTransformation, Coordinate coord);

	Matrix<3, 3, double> _buildTranslationMatrix(Coordinate position);
	Matrix<3, 3, double> _buildExpansionMatrix(double x_factor, double y_factor);
	Matrix<3, 3, double> _buildRotationMatrix(double angle);
};

#endif /* SRC_GRAPHICOBJECT_H_ */
