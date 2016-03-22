/*
 * Point.h
 *
 *  Created on: 17 de ago de 2015
 *      Author: plab
 */

#ifndef SRC_GRAPHICOBJECT_POINT_H_
#define SRC_GRAPHICOBJECT_POINT_H_

#include <string>

#include "GraphicObject.hpp"

using namespace std;

class Point : public GraphicObject {

public:
	Point(string name, Coordinate coord);
};

#endif /* SRC_GRAPHICOBJECT_POINT_H_ */
