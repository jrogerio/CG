/*
 * World.h
 *
 * Author: joao
 */

#ifndef SRC_WORLD_H_
#define SRC_WORLD_H_

#include <string>

#include "GraphicObject.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Polygon.hpp"
#include "Window.hpp"

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
};

#endif /* SRC_WORLD_H_ */
