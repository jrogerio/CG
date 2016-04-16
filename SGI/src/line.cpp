#include "line.hpp"

Line::Line(string name, Coordinate first, Coordinate second) :
	GeometricObject(name, line, {first, second} ) {
}

vector<Coordinate> Line::applyClipping() {
	//return Clipper::cohenSutherland(_windowCoords);

	vector<Coordinate> clippedCoords;
	vector<Coordinate> emptyCoords;

	if(Clipper::liangBarsky(coords(), clippedCoords)) {
		_windowCoords = clippedCoords;
	} else {
		_windowCoords = emptyCoords;
	}

	return _windowCoords;
}

