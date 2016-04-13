#include "world.hpp"

World::World() : window(550, 550) {
	// TODO Auto-generated constructor stub
}

World::~World() {
	// TODO Auto-generated destructor stub
}

void World::addPoint(string name, Coordinate coord) {
	Point point(name, coord);
	normalize(point);

	_displayFile.push_back(point);
}

void World::addLine(string name, Coordinate begin, Coordinate end) {
	Line line(name, begin, end);
	normalize(line);

	_displayFile.push_back(line);
}

void World::addPolygon(string name, vector<Coordinate> coords) {
	Polygon polygon(name, coords);
	normalize(polygon);
	
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
	normalizeObjects();
}

void World::zoomWindow(int step) {
	window.zoom(step);
	normalizeObjects();
}

void World::rotateWindow(double angle) {
	window.rotate( DEG2RAD(angle) );
	normalizeObjects();
}

void World::normalizeObjects() {
	for (GraphicObject &object : _displayFile) {
		normalize(object);
	}
}

void World::normalize(GraphicObject& object) {
	SQUARE_MATRIX transformation = window.normalizedTransformation();
	object.normalizeIn(window.center(), window.xOffset(), window.yOffset(), transformation);
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
	normalize(*targetObject);
}

void World::scaleObject(string name, VECTOR factor) {
	GraphicObject* targetObject = &getObjectBy(name);
	targetObject->scaleTo(factor);
	normalize(*targetObject);
}

void World::rotateObject(string name, double angle) {
	GraphicObject* targetObject = &getObjectBy(name);
	targetObject->rotate( DEG2RAD(angle) );
	normalize(*targetObject);
}

void World::rotateObject(string name, double angle, Coordinate anchor) {
	GraphicObject* targetObject = &getObjectBy(name);
	targetObject->rotate(DEG2RAD(angle), anchor);
	normalize(*targetObject);
}

void World::exportToObj() {
	ObjectDescriptor* exporter = new ObjectDescriptor();

	for (int i = 0; i < _displayFile.size(); i++) {
		exporter->store(_displayFile[i].name(), _displayFile[i].type(), _displayFile[i].worldCoords());
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

	normalizeObjects();

	return names;
}
