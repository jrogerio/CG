/*
 * Window.h
 *
 *  Created on: 17 de ago de 2015
 *      Author: plab
 */

#ifndef SRC_WINDOW_H_
#define SRC_WINDOW_H_

#include <math.h>

#include "GraphicObject.h"

class Window {
public:
	Window(Coordinate lowerLeftCorner, Coordinate upperRightCorner);

	void move(Coordinate step);
	void zoom(int step);

	int Xmin();
	int Ymin();
	int Xmax();
	int Ymax();

private:
	Coordinate _lowerLeftCorner, _upperRightCorner;
};

#endif /* SRC_WINDOW_H_ */
