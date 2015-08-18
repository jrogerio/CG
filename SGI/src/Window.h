/*
 * Window.h
 *
 *  Created on: 17 de ago de 2015
 *      Author: plab
 */

#ifndef SRC_WINDOW_H_
#define SRC_WINDOW_H_

#include "GraphicObject.h"

class Window {
public:
	Window(Coordinate lowerLeftCorner, Coordinate upperRightCorner);
	void moveUp(int steps);
	void moveDown(int steps);
	void moveLeft(int steps);
	void moveRight(int steps);
	void zoomIn(int steps);
	void zoomOut(int steps);

private:
	Coordinate _lowerLeftCorner, _upperRightCorner;
};

#endif /* SRC_WINDOW_H_ */
