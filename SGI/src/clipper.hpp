#ifndef SRC_CLIPPER_HPP_
#define SRC_CLIPPER_HPP_

#include <algorithm>
#include <cmath>
#include <list>
#include <iostream>

#include "line.hpp"
#include "point.hpp"

struct ClippingPoint {

	ClippingPoint(Coordinate coord): _coord(coord), _artificial(false) {}
	ClippingPoint(Coordinate coord, bool artificial): _coord(coord), _artificial(artificial) {}

private:
	Coordinate _coord;
	bool _artificial;

public:
	Coordinate coord() {
		return _coord;
	}

	bool isArtificial() {
		return _artificial;
	}
};

class Clipper {
	static const unsigned int UP = 8;
	static const unsigned int DOWN = 4;
	static const unsigned int LEFT = 2;
	static const unsigned int RIGHT = 1;

	static const int SCN_MIN = -1;
	static const int SCN_MAX = 1;

private:
	static vector<Coordinate> applyCohenSutherland(vector<Coordinate> coords, vector<unsigned int> regionCodes);

	static bool isOutOfRange(Coordinate coord);
	static vector<double> calculateCoeficients(vector<double> p, vector<double> q);
	static bool hasIntersection(vector<Coordinate> firstLine, vector<Coordinate> secondLine, 
								Coordinate &intersection);

public:
	Clipper();
	virtual ~Clipper();

	//Point
	static vector<Coordinate> clipPoint(Coordinate coord);

	// Line
	static unsigned int regionCodeOf(Coordinate coord);
	static vector<Coordinate> cohenSutherland(vector<Coordinate> coords);
	
	static vector<Coordinate> liangBarsky(vector<Coordinate> coords);
	static vector<Coordinate> weilerAtherton(vector<Coordinate> coords);
};

#endif /* SRC_CLIPPER_HPP_ */
