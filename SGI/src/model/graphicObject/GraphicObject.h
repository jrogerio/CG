/*
 * GraphicObject.h
 *
 *  Created on: 17 de ago de 2015
 *      Author: plab
 */

#ifndef MODEL_GRAPHICOBJECT_GRAPHICOBJECT_H_
#define MODEL_GRAPHICOBJECT_GRAPHICOBJECT_H_

#include <string>
#include <list>

using namespace std;

struct Coordinate {

	Coordinate(double x, double y): _x(x), _y(y) {
	}

	double x() { return _x; }
	double y() { return _y; }

private:
	double _x,_y;
};

// ---------------------------

class GraphicObject {
public:
	GraphicObject(string name, list<Coordinate> coords);
	virtual ~GraphicObject();

	string name();
	string type();
	list<Coordinate> coords();

protected:
	string _name;
	string _type;
	list<Coordinate> _coords;
};

#endif /* MODEL_GRAPHICOBJECT_GRAPHICOBJECT_H_ */
