#include "line.hpp"

Line::Line(string name, Coordinate first, Coordinate second) :
	GraphicObject(name, line, vector<Coordinate>()) {
		_worldCoords.push_back(first);
		_worldCoords.push_back(second);
}

