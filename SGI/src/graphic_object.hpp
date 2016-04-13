#ifndef SRC_GRAPHICOBJECT_H_
#define SRC_GRAPHICOBJECT_H_

#include <string>
#include <vector>
#include <iostream>

#include "transformable_object.hpp"

using namespace std;

enum GraphicObjectType {
	point,
	line,
	polygon
};

// ---------------------------

class GraphicObject : public TransformableObject {
public:
	GraphicObject(string name,  GraphicObjectType type, vector<Coordinate> coords);
	virtual ~GraphicObject();

	string name() const;
	GraphicObjectType type() const;
	vector<Coordinate> coords() const;
	vector<Coordinate> worldCoords() const;
	Coordinate centroid() const;

	void normalizeIn(Coordinate windowCenter, double xOffset, double yOffset, SQUARE_MATRIX transformation);

	void translate(VECTOR deslocation);
	void scaleTo(VECTOR factors);
	void rotate(double radians);
	void rotate(double radians, Coordinate anchor);

private:
	void applyTransformation(vector<Coordinate>& coordSystem, SQUARE_MATRIX transfMatrix);
	void positionBasedTransformation(vector<Coordinate>& coordSystem, SQUARE_MATRIX targetTransformation, Coordinate coord);

protected:
	string _name;
	GraphicObjectType _type;
	vector<Coordinate> _worldCoords;
	vector<Coordinate> _windowCoords;
};

#endif /* SRC_GRAPHICOBJECT_H_ */
