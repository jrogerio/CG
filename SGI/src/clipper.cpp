/*
 * clipper.cpp
 *
 *  Created on: 14 de abr de 2016
 *      Author: plab
 */

#include "clipper.hpp"
#include <iostream>

Clipper::Clipper() {
	// TODO Auto-generated constructor stub

}

Clipper::~Clipper() {
	// TODO Auto-generated destructor stub
}

vector<Coordinate> Clipper::clipPoint(Coordinate coord) {
	bool outOfRange = fabs(coord._x) > 1 || fabs(coord._y) > 1;

	if (outOfRange)
		return vector<Coordinate>();

	return {coord};
}

unsigned int Clipper::regionCodeOf(Coordinate coord) {
	unsigned int code = 0;
	std::cout << "\nrcCoord: (" << coord._x << ", " << coord._y << ")" << std::endl;

	//Using bitwise operators to represent region code.
	code = (coord._y > SCN_MAX) ? (code | UP) : code;
	std::cout << "\nCode: (" << code << std::endl;
	code = (coord._y < SCN_MIN) ? (code | DOWN) : code;
	std::cout << "\nCode: (" << code << std::endl;
	code = (coord._x > SCN_MAX) ? (code | RIGHT) : code;
	std::cout << "\nCode: (" << code << std::endl;
	code = (coord._x < SCN_MIN) ? (code | LEFT) : code;
	std::cout << "\nCode: (" << code << std::endl;

	return code;
}

vector<Coordinate> Clipper::cohenSutherland(vector<Coordinate> coords) {

	unsigned int rcBegin = regionCodeOf(coords[0]);
	unsigned int rcEnd = regionCodeOf(coords[1]);

	std::cout << "\nrcBegin: " << rcBegin << std::endl;
	std::cout << "\nrcEnd: " << rcEnd << std::endl;
	bool insideWindow = rcBegin == 0 && rcEnd == 0;
	if (insideWindow) {
		std::cout << "\n Dentro da janela totalmente" << std::endl;
		return coords;
	}

	bool outsideWindow = (rcBegin & rcEnd) != 0;
	if (outsideWindow) {
		std::cout << "\n Dentro da janela totalmente" << std::endl;
		return vector<Coordinate>();
	}

	std::cout << "\nInterseccao: " << (rcBegin & rcEnd) << std::endl;
	return applyCohenSutherland(coords, {rcBegin, rcEnd});
}

vector<Coordinate> Clipper::applyCohenSutherland(vector<Coordinate> coords, vector<unsigned int> regionCodes) {
	double m = (coords[1]._y - coords[0]._y) / (coords[1]._x - coords[0]._x);

	vector<Coordinate> clippedCoords;
	double x,y;

	for (int i = 0; i < coords.size(); ++i) {

		if (regionCodes[i] & LEFT) {
			y = m * (SCN_MIN - coords[i]._x) + coords[i]._y;
			clippedCoords.push_back( Coordinate(SCN_MIN, y) );
			std::cout << "\nClipped: (" << SCN_MIN << ", " << y << ")" << std::endl;

			continue;
		}
		if (regionCodes[i] & RIGHT) {
			y = m * (SCN_MAX - coords[i]._x) + coords[i]._y;
			clippedCoords.push_back( Coordinate(SCN_MAX, y) );
			std::cout << "\nClipped: (" << SCN_MAX << ", " << y << ")" << std::endl;

			continue;
		}
		if (regionCodes[i] & UP) {
			x = coords[i]._x + 1 / m * (SCN_MAX - coords[i]._y);
			clippedCoords.push_back( Coordinate(x, SCN_MAX) );
			std::cout << "\nClipped: (" << x << ", " << SCN_MAX << ")" << std::endl;

			continue;
		}
		if (regionCodes[i] & DOWN) {
			x = coords[i]._x + 1 / m * (SCN_MIN - coords[i]._y);
			clippedCoords.push_back( Coordinate(x, SCN_MIN) );
			std::cout << "\nClipped: (" << SCN_MIN << ", " << SCN_MIN << ")" << std::endl;

			continue;
		}

		clippedCoords.push_back(coords[i]);
	}

	return clippedCoords;
}
