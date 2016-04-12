#include "world.hpp"

World::World() : window(Coordinate(0,0), Coordinate(550, 550)) {
	// TODO Auto-generated constructor stub
}

World::~World() {
	// TODO Auto-generated destructor stub
}

void World::addPoint(string name, Coordinate point) {
	_displayFile.push_back(Point(name, point));
}

void World::addLine(string name, Coordinate begin, Coordinate end) {
	_displayFile.push_back(Line(name, begin, end));
}

void World::addPolygon(string name, vector<Coordinate> coords) {
	_displayFile.push_back(Polygon(name, coords));
}

vector<GraphicObject> World::getObjects(){
	return _displayFile;
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

vector<string> World::importFromObj(string filePath) {
	ObjectDescriptor* importer = new ObjectDescriptor();
	vector<string> names;

	_displayFile = importer->parse(filePath);

	for (int i = 0; i < _displayFile.size(); i++) {
		names.push_back(_displayFile[i].name());
	}

	return names;
}
