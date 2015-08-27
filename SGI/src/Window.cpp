/*
 * Window.cpp
 *
 *  Created on: 17 de ago de 2015
 *      Author: plab
 */

#include "Window.h"

Window::Window(Coordinate lowerLeftCorner, Coordinate upperRightCorner) :
		_lowerLeftCorner(lowerLeftCorner), _upperRightCorner(upperRightCorner) {

}

void Window::moveUp(int steps) {
	_lowerLeftCorner._y += steps;
	_upperRightCorner._y += steps;
}

void Window::moveDown(int steps) {
	_lowerLeftCorner._y -= steps;
	_upperRightCorner._y -= steps;
}

void Window::moveLeft(int steps) {
	_lowerLeftCorner._x -= steps;
	_upperRightCorner._x -= steps;
}

void Window::moveRight(int steps) {
	_lowerLeftCorner._x += steps;
	_upperRightCorner._x += steps;
}

void Window::zoomIn(int steps) {
	_lowerLeftCorner._x -= steps;
	_lowerLeftCorner._y -= steps;
	_upperRightCorner._x -= steps;
	_upperRightCorner._y -= steps;
}

void Window::zoomOut(int steps) {
	_lowerLeftCorner._x += steps;
	_lowerLeftCorner._y += steps;
	_upperRightCorner._x += steps;
	_upperRightCorner._y += steps;
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

