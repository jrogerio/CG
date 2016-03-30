#include "line.hpp"

Line::Line(string name, Coordinate first, Coordinate second) :
	GraphicObject(name, line, vector<Coordinate>()) {
		_coords.push_back(first);
		_coords.push_back(second);
}

