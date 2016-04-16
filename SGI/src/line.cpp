#include "line.hpp"
#include <iostream>

Line::Line(string name, Coordinate first, Coordinate second) :
	GeometricObject(name, line, {first, second} ) {
}

void Line::applyClipping() {
	vector<Coordinate> clippedCoords;
	vector<Coordinate> emptyCoords;

	if(Clipper::liangBarsky(coords(), clippedCoords)) {
		_windowCoords = clippedCoords;
	} else {
		_windowCoords = emptyCoords;
	}
}
