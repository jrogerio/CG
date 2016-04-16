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

bool Clipper::liangBarsky(vector<Coordinate> coords, vector<Coordinate> &clippedCoords) {
	double xWindowMin = -1.0;
	double xWindowMax = 1.0; 
	double yWindowMin = -1.0;
	double yWindowMax = 1.0; 

	double t0 = 0.0; 
	double t1 = 1.0;
	double xDelta = coords[1]._x - coords[0]._x;
	double yDelta = coords[1]._y - coords[0]._y;
	double p,q,r;

	for(int edge=0; edge<4; edge++) {
		if (edge==0) {p = -xDelta; q = (coords[0]._x - xWindowMin);  }
		if (edge==1) {p = xDelta;  q = (xWindowMax - coords[0]._x); }
		if (edge==2) {p = -yDelta; q = (coords[0]._y - yWindowMin);}
		if (edge==3) {p = yDelta;  q = (yWindowMax - coords[0]._y);   }   
		
		r = q/p;
		
		if(p==0 && q<0) 
			return false;

		if(p<0) {
			if(r>t1) 
				return false;
			else if(r>t0) 
				t0=r;
		} else if(p>0) {
			if(r<t0) 
				return false;
			else if(r<t1) 
				t1=r;
		}
	}

	clippedCoords.push_back(Coordinate((coords[0]._x + t0 * xDelta), (coords[0]._y + t0 * yDelta)));
	clippedCoords.push_back(Coordinate((coords[1]._x + t1 * xDelta), (coords[1]._y + t1 * yDelta)));

	return true;
}
