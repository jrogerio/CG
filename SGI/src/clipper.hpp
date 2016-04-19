#ifndef SRC_CLIPPER_HPP_
#define SRC_CLIPPER_HPP_

#include <algorithm>
#include <cmath>
#include <list>
#include <iostream>

#include "geometric_object.hpp"

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

	bool equals(ClippingPoint other) {
		if(_coord._x == other.coord()._x && _coord._y == other.coord()._y && _artificial == other.isArtificial())
			return true;

		return false;
	}
};

enum ClippingAlgorithm {
	LIANG_BARSKY,
	COHEN_SUTHERLAND
};

typedef vector<CLIPPED_OBJECT> (*ClippingFunction)(vector<Coordinate>);

class Clipper {
	static const unsigned int UP = 8;
	static const unsigned int DOWN = 4;
	static const unsigned int LEFT = 2;
	static const unsigned int RIGHT = 1;

	static const int SCN_MIN = -1;
	static const int SCN_MAX = 1;


private:

	static vector<CLIPPED_OBJECT> applyCohenSutherland(vector<Coordinate> coords, vector<unsigned int> regionCodes);

	static bool isOutOfRange(Coordinate coord);
	static vector<double> calculateCoeficients(vector<double> p, vector<double> q);
	static bool hasIntersection(vector<Coordinate> firstLine, vector<Coordinate> secondLine, 
								Coordinate &intersection);

	static list<ClippingPoint>::iterator getIterator(ClippingPoint object, list<ClippingPoint>* container);

public:
	Clipper();
	virtual ~Clipper();

	static ClippingFunction clippingFunction;

	//Point
	static vector<CLIPPED_OBJECT> clipPoint(Coordinate coord);

	// Line
	static void setClippingAlgorithm(ClippingAlgorithm algorithm);
	static unsigned int regionCodeOf(Coordinate coord);
	static vector<CLIPPED_OBJECT> cohenSutherland(vector<Coordinate> coords);
	static vector<CLIPPED_OBJECT> liangBarsky(vector<Coordinate> coords);

	static vector<Coordinate> weilerAtherton(vector<Coordinate> coords);
};

#endif /* SRC_CLIPPER_HPP_ */
