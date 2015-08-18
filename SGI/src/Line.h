/*
 * Line.h
 *
 *  Created on: 17 de ago de 2015
 *      Author: plab
 */

#ifndef SRC_LINE_H_
#define SRC_LINE_H_

#include <string>

#include "GraphicObject.h"

using namespace std;

class Line : GraphicObject{
public:
	Line(string name, Coordinate first, Coordinate second);
};

#endif /* SRC_LINE_H_ */
