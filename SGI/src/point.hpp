#ifndef SRC_GRAPHICOBJECT_POINT_H_
#define SRC_GRAPHICOBJECT_POINT_H_

#include <string>
#include "graphic_object.hpp"

using namespace std;

class Point : public GraphicObject {

public:
	Point(string name, Coordinate coord);
};

#endif /* SRC_GRAPHICOBJECT_POINT_H_ */
