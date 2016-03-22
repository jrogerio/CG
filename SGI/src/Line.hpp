/*
 * Line.h
 *
 * Author: plab
 */

#ifndef SRC_LINE_H_
#define SRC_LINE_H_

#include <string>

#include "GraphicObject.hpp"

using namespace std;

class Line : public GraphicObject{
public:
	Line(string name, Coordinate first, Coordinate second);
};

#endif /* SRC_LINE_H_ */
