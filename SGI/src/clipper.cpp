/*
 * clipper.cpp
 *
 *  Created on: 14 de abr de 2016
 *      Author: plab
 */

#include "clipper.hpp"
#include <iostream>

Clipper::Clipper() {
	// TODO Auto-generated constructor stub

}

Clipper::~Clipper() {
	// TODO Auto-generated destructor stub
}


unsigned int Clipper::regionCodeOf(Coordinate coord) {
	unsigned int code = 0;

	code = (coord._y > SCN_MAX) ? code | UP : code;
	code = (coord._y < SCN_MIN) ? code | DOWN : code;
	code = (coord._x > SCN_MAX) ? code | RIGHT : code;
	code = (coord._x < SCN_MIN) ? code | LEFT : code;

	return code;
}

void Clipper::cohenSutherland(vector<Coordinate> coords) {

	unsigned int rcBegin = regionCodeOf(coords[0]);
	unsigned int rcEnd = regionCodeOf(coords[1]);

	bool insideWindow = !rcBegin && !rcEnd;
	if (insideWindow) {
		std::cout << "\n Dentro da janela totalmente" << std::endl;
		return;
	}

	std::cout << "\nInterseccao: " << (rcBegin & rcEnd) << std::endl;
}
