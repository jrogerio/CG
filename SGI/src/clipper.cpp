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

	//Using bitwise operators to represent region code.
	code = (coord._y > SCN_MAX) ? (code | UP) : code;
	code = (coord._y < SCN_MIN) ? (code | DOWN) : code;
	code = (coord._x > SCN_MAX) ? (code | RIGHT) : code;
	code = (coord._x < SCN_MIN) ? (code | LEFT) : code;

	return code;
}

vector<Coordinate> Clipper::cohenSutherland(vector<Coordinate> coords) {
	unsigned int rcBegin = regionCodeOf(coords[0]);
	unsigned int rcEnd = regionCodeOf(coords[1]);

	bool insideWindow = !rcBegin && !rcEnd;
	if (insideWindow) 
		return coords;

	bool partiallyInside = (rcBegin != rcEnd) && ( !(rcBegin & rcEnd) );
	if (partiallyInside)
		return applyCohenSutherland(coords, {rcBegin, rcEnd});
	
	return vector<Coordinate>();
}

vector<Coordinate> Clipper::applyCohenSutherland(vector<Coordinate> coords, vector<unsigned int> regionCodes) {
	double m = (coords[1]._y - coords[0]._y) / (coords[1]._x - coords[0]._x);

	vector<Coordinate> clippedCoords;
	double x,y;

	for (int i = 0; i < coords.size(); ++i) {

		if (regionCodes[i] & LEFT) {
			y = m * (SCN_MIN - coords[i]._x) + coords[i]._y;
			clippedCoords.push_back( Coordinate(SCN_MIN, y) );

			continue;
		}
		if (regionCodes[i] & RIGHT) {
			y = m * (SCN_MAX - coords[i]._x) + coords[i]._y;
			clippedCoords.push_back( Coordinate(SCN_MAX, y) );

			continue;
		}
		if (regionCodes[i] & UP) {
			x = coords[i]._x + 1 / m * (SCN_MAX - coords[i]._y);
			clippedCoords.push_back( Coordinate(x, SCN_MAX) );

			continue;
		}
		if (regionCodes[i] & DOWN) {
			x = coords[i]._x + 1 / m * (SCN_MIN - coords[i]._y);
			clippedCoords.push_back( Coordinate(x, SCN_MIN) );

			continue;
		}

		clippedCoords.push_back(coords[i]);
	}

	return clippedCoords;
}

vector<Coordinate> Clipper::liangBarsky(vector<Coordinate> coords) {
	vector<Coordinate> clippedCoords;

	double dx = coords[1]._x - coords[0]._x;
	double dy = coords[1]._y - coords[0]._y;

	double p1 = -dx;
	double p2 = dx;
	double p3 = -dy;
	double p4 = dy;

	double q1 = coords[0]._x - SCN_MIN;
	double q2 = SCN_MAX - coords[0]._x;
	double q3 = coords[0]._y - SCN_MIN;
	double q4 = SCN_MAX - coords[0]._y;

	bool outsideWindow = (!p1 && q1 < 0) || (!p3 && q3 < 0) ||
						(!p2 && q2 < 0) || (!p4 && q4 < 0);

	if (outsideWindow)
		return vector<Coordinate>();

	double coeficient1, coeficient2, r1, r2, x, y;

	// calculo primeiro ponto
	r1 = (p1 < 0) ? (q1 / p1) : (q2 / p2);
	r2 = (p3 < 0) ? (q3 / p3) : (q4 / p4);

	r1 = (!isfinite(r1)) ? 0.0 : r1;
	r2 = (!isfinite(r2)) ? 0.0 : r2;

	coeficient1 = max(0.0, max(r1,r2));

	if (coeficient1 > 0) {
		x = coords[0]._x + coeficient1 * dx;
		y = coords[0]._y + coeficient1 * dy;

		clippedCoords.push_back( Coordinate(x,y) );
	} else {
		clippedCoords.push_back( coords[0] );
	}

	r1 = (p2 < 0) ? (q1 / p1) : (q2 / p2);
	r2 = (p4 < 0) ? (q3 / p3) : (q4 / p4);

	r1 = (!isfinite(r1)) ? 1.0 : r1;
	r2 = (!isfinite(r2)) ? 1.0 : r2;

	coeficient2 = min(1.0, min(r1,r2));

	if (coeficient2 < 1) {
		x = coords[0]._x + coeficient2 * dx;
		y = coords[0]._y + coeficient2 * dy;

		clippedCoords.push_back( Coordinate(x,y) );
	} else {
		clippedCoords.push_back( coords[1] );
	}

	if (coeficient1 <= coeficient2)
		return clippedCoords;
	else 
		return vector<Coordinate>();
}
