/*
 * GraphicObject.h
 *
 *  Created on: 17 de ago de 2015
 *      Author: plab
 */

#ifndef SRC_GRAPHICOBJECT_GRAPHICOBJECT_H_
#define SRC_GRAPHICOBJECT_GRAPHICOBJECT_H_

#include <string>
#include <vector>

using namespace std;

struct Coordinate {

	Coordinate(double x, double y): _x(x), _y(y) {
	}

	double x() { return _x; }
	double y() { return _y; }

private:
	double _x,_y;
};

enum class GraphicObjectType {
	POINT,
	LINE,
	POLYGON
};

// ---------------------------

class GraphicObject {
public:
	GraphicObject(string name,  GraphicObjectType type, vector<Coordinate> coords);
	virtual ~GraphicObject();

	string name();
	GraphicObjectType type();
	vector<Coordinate> coords();

protected:
	string _name;
	GraphicObjectType _type;
	vector<Coordinate> _coords;
};

#endif /* SRC_GRAPHICOBJECT_GRAPHICOBJECT_H_ */
