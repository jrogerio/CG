#ifndef SRC_WINDOW_H_
#define SRC_WINDOW_H_

#include <algorithm>
#include "matrix.hpp"

#define VECTOR Coordinate

#define SQUARE_MATRIX Matrix<3,3>
#define ROW_VECTOR Matrix<1,3>

struct Coordinate {

	Coordinate(double x, double y): _x(x), _y(y) {}
	Coordinate(): _x(0), _y(0) {}

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

	double length() {
		return sqrt( pow(_x, 2) + pow(_y, 2) );
	}

	double dotProduct( Coordinate other ) {
		return (_x * other._x) + (_y * other._y);
	}

	double angleWith( Coordinate target ) {
		return dotProduct(target) / (length() * target.length());
	}
};

class Window {
public:
	Window(Coordinate lowerLeftCorner, Coordinate upperRightCorner);

	void move(Coordinate step);
	void zoom(int step);

	Coordinate center();

	double xOffset();
	double yOffset();

	int Xmin();
	int Ymin();
	int Xmax();
	int Ymax();

private:
	Coordinate _lowerLeftCorner, _upperRightCorner, _center;
	Coordinate _vupVector;

	double _xOffset, _yOffset;
};

#endif /* SRC_WINDOW_H_ */
