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
	Line line(name, begin, end);
	line.rotate(45);

	displayFile.push_back(line);
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

void World::moveUpWindow(int step) {
	window.move( Coordinate(0, step) );
}

void World::moveDownWindow(int step) {
	window.move( Coordinate(0, -step) );
}

void World::moveLeftWindow(int step) {
	window.move( Coordinate(-step, 0) );
}

void World::moveRightWindow(int step) {
	window.move( Coordinate(step, 0) );
}

void World::zoomInWindow(int step) {
	window.zoom(step);
}

void World::zoomOutWindow(int step) {
	window.zoom(-step);
}

GraphicObject& World::getObjectBy(string name) {
	for (int i = 0; i < displayFile.size(); i++) {
		if(displayFile[i].name() == name) {
			return displayFile[i];
		}
	}
}

void World::translateObject(string name, double x, double y) {
	GraphicObject* targetObject = &getObjectBy(name);
	targetObject->translate(Coordinate(x, y));
}

void World::scaleObject(string name, double x, double y) {
	GraphicObject* targetObject = &getObjectBy(name);
	targetObject->scaleTo(VECTOR(x, y));
}

void World::rotateObject(string name, double angle) {
	GraphicObject* targetObject = &getObjectBy(name);
	targetObject->rotate(angle);
}

void World::rotateObject(string name, double angle, Coordinate anchor) {
	GraphicObject* targetObject = &getObjectBy(name);
	targetObject->rotate(angle, anchor);
}
