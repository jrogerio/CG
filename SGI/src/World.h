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
#include "Line.h"

using namespace std;

class World {
private:
	vector<GraphicObject> displayFile;

public:
	World();
	virtual ~World();

	void addLine(string name, Coordinate begin, Coordinate end);
	vector<GraphicObject> getObjects();
};

#endif /* SRC_WORLD_H_ */
