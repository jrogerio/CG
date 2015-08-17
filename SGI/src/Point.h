/*
 * Point.h
 *
 *  Created on: 17 de ago de 2015
 *      Author: plab
 */

#ifndef MODEL_GRAPHICOBJECT_POINT_H_
#define MODEL_GRAPHICOBJECT_POINT_H_

#include <string>
#include <list>

#include "GraphicObject.h"

using namespace std;

class Point : public GraphicObject {
private:
	//const string POINT_TYPE = "point";

public:
	Point(string name, list<Coordinate> coords);
	virtual ~Point();
};

#endif /* MODEL_GRAPHICOBJECT_POINT_H_ */
