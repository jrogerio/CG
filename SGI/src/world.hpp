#ifndef SRC_WORLD_H_
#define SRC_WORLD_H_

#include <string>
#include "graphic_object.hpp"
#include "point.hpp"
#include "line.hpp"
#include "polygon.hpp"
#include "window.hpp"
#include "object_descriptor.hpp"

using namespace std;

class World {
private:
	vector<GraphicObject> _displayFile;
	Window window;

public:
	World();
	virtual ~World();

	void addPoint(string name, Coordinate coord);
	void addLine(string name, Coordinate begin, Coordinate end);
	void addPolygon(string name, vector<Coordinate> coords);
	vector<GraphicObject> getObjects();

	Window getWindow();

	void moveWindow(VECTOR step);
	void zoomWindow(int step);

	GraphicObject& getObjectBy(string name);

	void translateObject(string name, VECTOR deslocation);
	void scaleObject(string name, VECTOR factor);
	void rotateObject(string name, double angle);
	void rotateObject(string name, double angle, Coordinate anchor);

	void exportToObj();
	vector<string> importFromObj(string filePath);
};

#endif /* SRC_WORLD_H_ */
