/*
 * World.cpp
 *
 *  Created on: 19 de ago de 2015
 *      Author: joao
 */

#include "World.h"

World::World() : window(Coordinate(0,0), Coordinate(550,200)) {
	// TODO Auto-generated constructor stub
}

World::~World() {
	// TODO Auto-generated destructor stub
}

void World::addPoint(string name, Coordinate point) {
	displayFile.push_back(Point(name, point));
}

void World::addLine(string name, Coordinate begin, Coordinate end) {
	displayFile.push_back(Line(name, begin, end));
}

void World::addPolygon(string name, vector<Coordinate> coords) {
	displayFile.push_back(Polygon(name, coords));
}

vector<GraphicObject> World::getObjects(){
	return displayFile;
}

Window World::getWindow() {
	return window;
}
