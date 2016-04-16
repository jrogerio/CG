/*
 * clipper.hpp
 *
 *  Created on: 14 de abr de 2016
 *      Author: plab
 */

#ifndef SRC_CLIPPER_HPP_
#define SRC_CLIPPER_HPP_

#include "geometric_object.hpp"

class Clipper {
	static const unsigned int UP = 8;
	static const unsigned int DOWN = 4;
	static const unsigned int LEFT = 2;
	static const unsigned int RIGHT = 1;

	static const int SCN_MIN = -1;
	static const int SCN_MAX = 1;

public:
	Clipper();
	virtual ~Clipper();

	//Point
	// static Point clipPoint(Point point);

	// Line
	static unsigned int regionCodeOf(Coordinate coord);
	static void cohenSutherland(vector<Coordinate> coords);
	static bool liangBarsky(vector<Coordinate> coords, vector<Coordinate> &clippedCoords);
};

#endif /* SRC_CLIPPER_HPP_ */
