/*
 * World.cpp
 *
 *  Created on: 19 de ago de 2015
 *      Author: joao
 */

#include "World.h"

World::World() {
	// TODO Auto-generated constructor stub
}

World::~World() {
	// TODO Auto-generated destructor stub
}

void World::addLine(string name, Coordinate begin, Coordinate end) {
	displayFile.push_back(Line(name, begin, end));
}

vector<GraphicObject> World::getObjects(){
	return vector<GraphicObject>();
}
