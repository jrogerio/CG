#include "window.hpp"

Window::Window(double width, double height) :
		_width(width),
		_height(height),
		_center(0,0),
		_vupVector(0,1) {
		}

void Window::move(Coordinate step) {
	double xFactor = _width * step._x / 100.0;
	double yFactor = _height * step._y / 100.0;

	_center._x += xFactor;
	_center._y += yFactor;
}

void Window::rotate(double angle) {
	SQUARE_MATRIX rotationMatrix = _buildRotationMatrix(angle);
	ROW_VECTOR vupMatrix = _vupVector.toHomogenousMatrix();
	ROW_VECTOR result = vupMatrix * rotationMatrix;

	_vupVector._x = result.valueOn(0,0);
	_vupVector._y = result.valueOn(0,1);

//	if (fabs(_vupVector._x) < 0.00000001)
//		_vupVector._x = 0;
//
//	if (fabs(_vupVector._y) < 0.00000001)
//			_vupVector._y = 0;

	std::cout << "\nreultado vup: (" << _vupVector._x << ", " << _vupVector._y <<")" << std::endl;
}

void Window::zoom(int step) {
	double xFactor = min<double>(xOffset(), xOffset() * step / 100.0);
	double yFactor = min<double>(yOffset(), yOffset() * step / 100.0);

	_width -= (2 * xFactor);
	_height -= (2 * yFactor);
}

Coordinate Window::center() {
	return _center;
}

double Window::xOffset() {
	return _width / 2;
}

double Window::yOffset() {
	return _height / 2;
}

SQUARE_MATRIX Window::normalizedTransformation() {
	double angle = _vupVector.angleWith( Coordinate(0,1) );

	SQUARE_MATRIX translationMatrix = _buildTranslationMatrix( _center.negate() );
	SQUARE_MATRIX rotationMatrix = _buildRotationMatrix( -angle );

	return translationMatrix * rotationMatrix;
}

