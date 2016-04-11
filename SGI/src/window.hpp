#ifndef SRC_WINDOW_H_
#define SRC_WINDOW_H_

#include <cmath>
#include "graphic_object.hpp"
#include "matrix.hpp"

struct MathVector {
	double _x,_y;

public:
	MathVector(double x, double y): _x(x), _y(y) {}

	double length() {
		return sqrt( pow(_x, 2) + pow(_y, 2) );
	}

	double dotProduct( MathVector other ) {
		return (_x * other._x) + (_y * other._y);
	}

	double angleWith( MathVector target ) {
		return dotProduct(target) / (length() * target.length());
	}
};

class Window {
public:
	Window(Coordinate lowerLeftCorner, Coordinate upperRightCorner);

	void move(Coordinate step);
	void zoom(int step);

	int Xmin();
	int Ymin();
	int Xmax();
	int Ymax();

private:
	Coordinate _lowerLeftCorner, _upperRightCorner, _center;
	MathVector _vupVector;

	double _width, _height;
};

#endif /* SRC_WINDOW_H_ */
