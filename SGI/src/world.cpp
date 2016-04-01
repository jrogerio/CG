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

void World::translateObject(char *name, double x, double y) {
	for (int i = 0; i < displayFile.size(); i++) {
		if(displayFile[i].name() == name) {
			GraphicObject updatedObject = displayFile[i];
			updatedObject.translate(Coordinate(x, y));

			displayFile[i] = updatedObject;

			break;
		}
	}
}

void World::scaleObject(char *name, double x, double y) {
	for (int i = 0; i < displayFile.size(); i++) {
		if(displayFile[i].name() == name) {
			GraphicObject updatedObject = displayFile[i];
			updatedObject.scaleTo(Vector(x, y));

			displayFile[i] = updatedObject;

			break;
		}
	}
}

void World::rotateObject(char *name, double angle) {
	for (int i = 0; i < displayFile.size(); i++) {
		if(displayFile[i].name() == name) {
			GraphicObject updatedObject = displayFile[i];
			updatedObject.rotate(angle);

			displayFile[i] = updatedObject;

			break;
		}
	}
}