/*
 * clipper.hpp
 *
 *  Created on: 14 de abr de 2016
 *      Author: plab
 */

#ifndef SRC_CLIPPER_HPP_
#define SRC_CLIPPER_HPP_

#include <algorithm>
#include <cmath>

#include "line.hpp"
#include "point.hpp"

class Clipper {
	static const unsigned int UP = 8;
	static const unsigned int DOWN = 4;
	static const unsigned int LEFT = 2;
	static const unsigned int RIGHT = 1;

	static const int SCN_MIN = -1;
	static const int SCN_MAX = 1;

private:
	static vector<Coordinate> applyCohenSutherland(vector<Coordinate> coords, vector<unsigned int> regionCodes);

public:
	Clipper();
	virtual ~Clipper();

	//Point
	static vector<Coordinate> clipPoint(Coordinate coord);

	// Line
	static unsigned int regionCodeOf(Coordinate coord);
	static vector<Coordinate> cohenSutherland(vector<Coordinate> coords);
	
	static vector<Coordinate> liangBarsky(vector<Coordinate> coords);
};

#endif /* SRC_CLIPPER_HPP_ */
