#include "world.hpp"

World::World() : window(Coordinate(0,0), Coordinate(550, 550)) {
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

void World::moveWindow(VECTOR step) {
	window.move(step);
}

void World::zoomWindow(int step) {
	window.zoom(step);
}

GraphicObject& World::getObjectBy(string name) {
	for (int i = 0; i < displayFile.size(); i++) {
		if(displayFile[i].name() == name) {
			return displayFile[i];
		}
	}
}

void World::translateObject(string name, VECTOR deslocation) {
	GraphicObject* targetObject = &getObjectBy(name);
	targetObject->translate(deslocation);
}

void World::scaleObject(string name, VECTOR factor) {
	GraphicObject* targetObject = &getObjectBy(name);
	targetObject->scaleTo(factor);
}

void World::rotateObject(string name, double angle) {
	GraphicObject* targetObject = &getObjectBy(name);
	targetObject->rotate(angle);
}

void World::rotateObject(string name, double angle, Coordinate anchor) {
	GraphicObject* targetObject = &getObjectBy(name);
	targetObject->rotate(angle, anchor);
}
