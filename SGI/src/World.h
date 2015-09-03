/*
 * World.h
 *
 *  Created on: 19 de ago de 2015
 *      Author: joao
 */

#ifndef SRC_WORLD_H_
#define SRC_WORLD_H_

#include <string.h>

#include "GraphicObject.h"
#include "Point.h"
#include "Line.h"
#include "Polygon.h"
#include "Window.h"

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
