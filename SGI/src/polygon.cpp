#include "polygon.hpp"

Polygon::Polygon(string name, vector<Coordinate> coords, bool filled) :
		GeometricObject(name, polygon, coords, filled) {}

vector<Coordinate> Polygon::applyClipping() {
	return vector<Coordinate>();
}
