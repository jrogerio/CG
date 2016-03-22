/*
 * Window.cpp
 *
 * Author: plab
 */

#include "Window.hpp"

Window::Window(Coordinate lowerLeftCorner, Coordinate upperRightCorner) :
		_lowerLeftCorner(lowerLeftCorner), _upperRightCorner(upperRightCorner) {

}

void Window::move(Coordinate step) {
	double xFactor = (_upperRightCorner._x - _lowerLeftCorner._x) * step._x / 100.0;
	double yFactor = (_upperRightCorner._y - _lowerLeftCorner._y) * step._y / 100.0;

	_lowerLeftCorner._x += xFactor;
	_upperRightCorner._x += xFactor;

	_lowerLeftCorner._y += yFactor;
	_upperRightCorner._y += yFactor;
}

void Window::zoom(int step) {
	int halfWidth = (_upperRightCorner._x - _lowerLeftCorner._x) / 2;
	int halfHeight = (_upperRightCorner._y - _lowerLeftCorner._y) / 2;

	double xFactor = min<double>(halfWidth - 1, halfWidth * step / 100.0);
	double yFactor = min<double>(halfHeight - 1, halfHeight * step / 100.0);

	_lowerLeftCorner._x += xFactor;
	_lowerLeftCorner._y += yFactor;
	_upperRightCorner._x -= xFactor;
	_upperRightCorner._y -= yFactor;
}

int Window::Xmin() {
	return _lowerLeftCorner._x;
}

int Window::Ymin() {
	return _lowerLeftCorner._y;
}

int Window::Xmax() {
	return _upperRightCorner._x;
}

int Window::Ymax() {
	return _upperRightCorner._y;
}

