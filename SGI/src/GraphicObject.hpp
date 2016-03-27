/*
 * GraphicObject.h
 *
 * Author: plab
 */

#ifndef SRC_GRAPHICOBJECT_H_
#define SRC_GRAPHICOBJECT_H_

#include <string>
#include <vector>

using namespace std;

struct Coordinate {

	Coordinate(double x, double y): _x(x), _y(y) {}

public:
	double _x,_y;
};

enum GraphicObjectType {
	point,
	line,
	polygon
};

// ---------------------------

class GraphicObject {
public:
	GraphicObject(string name,  GraphicObjectType type, vector<Coordinate> coords);
	virtual ~GraphicObject();

	string name() const;
	GraphicObjectType type() const;
	vector<Coordinate> coords() const;
	Coordinate centroid() const;

protected:
	string _name;
	GraphicObjectType _type;
	vector<Coordinate> _coords;
};

#endif /* SRC_GRAPHICOBJECT_H_ */
