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

	vector<double> p = {-dx, dx, -dy, dy};
	vector<double> q = {coords[0]._x - SCN_MIN,
		SCN_MAX - coords[0]._x,
		coords[0]._y - SCN_MIN,
		SCN_MAX - coords[0]._y};

	bool outsideWindow = (!p[0] && q[0] < 0) || (!p[2] && q[2] < 0) ||
						(!p[1] && q[1] < 0) || (!p[3] && q[3] < 0);

	if (outsideWindow)
		return vector<Coordinate>();

	double x, y;
	vector<double> coefs = calculateCoeficients(p, q);

	if (coefs[0] > coefs[1])
		return vector<Coordinate>();
	
	if (coefs[0] > 0) {
		x = coords[0]._x + coefs[0] * dx;
		y = coords[0]._y + coefs[0] * dy;

		clippedCoords.push_back( Coordinate(x,y) );
	} else {
		clippedCoords.push_back( coords[0] );
	}

	if (coefs[1] < 1) {
		x = coords[0]._x + coefs[1] * dx;
		y = coords[0]._y + coefs[1] * dy;

		clippedCoords.push_back( Coordinate(x,y) );
	} else {
		clippedCoords.push_back( coords[1] );
	}

	return clippedCoords;
}

vector<double> Clipper::calculateCoeficients(vector<double> p, vector<double> q) {
	vector<double> coefs;

	//Calculo dos valores para coordenada 1
	double r1 = (p[0] < 0) ? (q[0] / p[0]) : (q[1] / p[1]);
	double r2 = (p[2] < 0) ? (q[2] / p[2]) : (q[3] / p[3]);

	r1 = (!isfinite(r1)) ? 0.0 : r1;
	r2 = (!isfinite(r2)) ? 0.0 : r2;

	coefs.push_back( max(0.0, max(r1,r2)) );

	//Calculo dos valores para coordenada 2
	r1 = (p[1] < 0) ? (q[0] / p[0]) : (q[1] / p[1]);
	r2 = (p[3] < 0) ? (q[2] / p[2]) : (q[3] / p[3]);

	r1 = (!isfinite(r1)) ? 1.0 : r1;
	r2 = (!isfinite(r2)) ? 1.0 : r2;

	coefs.push_back( min(1.0, min(r1,r2)) );	

	return coefs;	
}