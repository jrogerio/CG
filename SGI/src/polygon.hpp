#ifndef SRC_POLYGON_H_
#define SRC_POLYGON_H_

#include <string>

#include "geometric_object.hpp"

using namespace std;

class Polygon : public GeometricObject {
public:
	Polygon(string name, vector<Coordinate> coords, bool filled);

	virtual vector<Coordinate> applyClipping();
};

#endif /* SRC_POLYGON_H_ */
