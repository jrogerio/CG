#ifndef SRC_WORLD_H_
#define SRC_WORLD_H_

#include <string>
#include "graphic_object.hpp"
#include "point.hpp"
#include "line.hpp"
#include "polygon.hpp"
#include "window.hpp"

using namespace std;

class World {
private:
	vector<GraphicObject> displayFile;
	Window window;

public:
	World();
	virtual ~World();

	void addPoint(string name, Coordinate point);
	void addLine(string name, Coordinate begin, Coordinate end);
	void addPolygon(string name, vector<Coordinate> coords);
	vector<GraphicObject> getObjects();

	Window getWindow();

	void moveUpWindow(int step);
	void moveDownWindow(int step);
	void moveLeftWindow(int step);
	void moveRightWindow(int step);
	void zoomInWindow(int step);
	void zoomOutWindow(int step);

	GraphicObject& getObjectBy(string name);

	void translateObject(string name, double x, double y);
	void scaleObject(string name, double x, double y);
	void rotateObject(string name, double angle);
	void rotateObject(string name, double angle, Coordinate anchor);
};

#endif /* SRC_WORLD_H_ */
