#include "world.hpp"

World::World() : window(Coordinate(0,0), Coordinate(550, 550)) {
	// TODO Auto-generated constructor stub
}

World::~World() {
	// TODO Auto-generated destructor stub
}

void World::addPoint(string name, Coordinate coord) {
	Point point(name, coord);
	point.normalizeIn(window.center(), window.xOffset(), window.yOffset());

	_displayFile.push_back(point);
}

void World::addLine(string name, Coordinate begin, Coordinate end) {
	Line line(name, begin, end);
	line.normalizeIn(window.center(), window.xOffset(), window.yOffset());
	
	_displayFile.push_back(line);
}

void World::addPolygon(string name, vector<Coordinate> coords) {
	Polygon polygon(name, coords);
	polygon.normalizeIn(window.center(), window.xOffset(), window.yOffset());
	
	_displayFile.push_back(polygon);
}

vector<GraphicObject> World::getObjects(){
	return _displayFile;
}

Window World::getWindow() {
	return window;
}

void World::moveWindow(VECTOR step) {
	window.move(step);
	printf("\n window center: (%f, %f)", window.center()._x, window.center()._y);

	for (GraphicObject &object : _displayFile) {
		object.normalizeIn(window.center(), window.xOffset(), window.yOffset());
	}
}

void World::zoomWindow(int step) {
	window.zoom(step);

	for (GraphicObject &object : _displayFile) {
		object.normalizeIn(window.center(), window.xOffset(), window.yOffset());
	}
}

GraphicObject& World::getObjectBy(string name) {
	for (int i = 0; i < _displayFile.size(); i++) {
		if(_displayFile[i].name() == name) {
			return _displayFile[i];
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

void World::exportToObj() {
	ObjectDescriptor* exporter = new ObjectDescriptor();

	for (int i = 0; i < _displayFile.size(); i++) {
		exporter->store(_displayFile[i].name(), _displayFile[i].type(), _displayFile[i].coords());
	}

	exporter->persist();
}
