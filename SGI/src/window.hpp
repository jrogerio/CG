#ifndef SRC_WINDOW_H_
#define SRC_WINDOW_H_

#include <algorithm>
#include <iostream>

#include "transformable_object.hpp"

class Window : public TransformableObject {
public:
	Window(double width, double height);

	void move(Coordinate step);
	void zoom(int step);
	void rotate(double angle);

	Coordinate center();

	double xOffset();
	double yOffset();

	SQUARE_MATRIX normalizedTransformation();

private:
	//Coordinate _lowerLeftCorner, _upperRightCorner;
	Coordinate _center;
	VECTOR _vupVector;

	double _width, _height;
};

#endif /* SRC_WINDOW_H_ */
