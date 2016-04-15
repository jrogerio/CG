#include "line.hpp"

Line::Line(string name, Coordinate first, Coordinate second) :
	GeometricObject(name, line, {first, second} ) {
}

vector<Coordinate> Line::applyClipping() {
	return Clipper::cohenSutherland(_windowCoords);
}

