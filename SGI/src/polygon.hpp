#ifndef SRC_POLYGON_H_
#define SRC_POLYGON_H_

#include <string>
#include "graphic_object.hpp"

using namespace std;

class Polygon : public GraphicObject {
public:
	Polygon(string name, vector<Coordinate> coords);
};

#endif /* SRC_POLYGON_H_ */
