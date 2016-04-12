#include "line.hpp"

Line::Line(string name, Coordinate first, Coordinate second) :
	GraphicObject(name, line, {first, second} ) {
}

