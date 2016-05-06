/*
 * b_spline.cpp
 *
 *  Created on: 5 de mai de 2016
 *      Author: plab
 */

#include "b_spline.h"
#include <iostream>

BSpline::BSpline(string name, vector<Coordinate> controlPoints, double step) :
	GeometricObject(name, cubic_bezier, {}) {
	// TODO Auto-generated constructor stub
	_generatePoints(controlPoints, step);
}

BSpline::~BSpline() {
	// TODO Auto-generated destructor stub
}

void BSpline::applyClipping() {
	_clippedObjects = { _windowCoords };
}

void BSpline::_generatePoints(vector<Coordinate> controlPoints, double step) {
	Matrix<4,4,double> inverseSplineMatrix = _buildInverseSplineMatrix();
	Matrix<4,4,double> initDiffMatrix = _buildDiffMatrix(step);
	Matrix<4,1,Coordinate> coefsMatrix;
	Matrix<4,1,Coordinate> fowardDiffMatrix;

	int curvesCount = controlPoints.size() - 3;

	for (int i = 0; i < curvesCount; i++) {
		coefsMatrix = inverseSplineMatrix * _buildGeometryMatrix(controlPoints, i);
		fowardDiffMatrix = initDiffMatrix * coefsMatrix;


	}
}

Matrix<4,1,double> BSpline::_buildGeometryMatrix(vector<Coordinate> controlPoints, int startIndex) {
	Matrix<4,1,Coordinate> geometryMatrix;

	geometryMatrix.setValueOn(0,0,controlPoints[startIndex++]);
	geometryMatrix.setValueOn(0,1,controlPoints[startIndex++]);
	geometryMatrix.setValueOn(0,2,controlPoints[startIndex++]);
	geometryMatrix.setValueOn(0,3,controlPoints[startIndex++]);

	return geometryMatrix;
}

Matrix<4,4,double> BSpline::_buildDiffMatrix(double step) {
	Matrix<4,4,double> diffMatrix;

	diffMatrix.setValueOn(0,0,0);
	diffMatrix.setValueOn(0,1,0);
	diffMatrix.setValueOn(0,2,0);
	diffMatrix.setValueOn(0,3,1);

	diffMatrix.setValueOn(1,0,pow(step, 3));
	diffMatrix.setValueOn(1,1,pow(step, 2));
	diffMatrix.setValueOn(1,2,step);
	diffMatrix.setValueOn(1,3,0);

	diffMatrix.setValueOn(2,0, (6 * pow(step, 3)) );
	diffMatrix.setValueOn(2,1, (2 * pow(step, 2)) );
	diffMatrix.setValueOn(2,2,0);
	diffMatrix.setValueOn(2,3,0);

	diffMatrix.setValueOn(3,0, (6 * pow(step, 3)) );
	diffMatrix.setValueOn(3,1,0);
	diffMatrix.setValueOn(3,2,0);
	diffMatrix.setValueOn(3,3,0);

	return diffMatrix;
}

Matrix<4,4, double> BSpline::_buildInverseSplineMatrix() {
	Matrix<4,4, double> inverseMatrix;

	inverseMatrix.setValueOn(0,0,0);
	inverseMatrix.setValueOn(0,1,(2.0/3.0));
	inverseMatrix.setValueOn(0,2,-1);
	inverseMatrix.setValueOn(0,3,1);

	inverseMatrix.setValueOn(1,0,0);
	inverseMatrix.setValueOn(1,1,(-1.0/3.0));
	inverseMatrix.setValueOn(1,2,0);
	inverseMatrix.setValueOn(1,3,1);

	inverseMatrix.setValueOn(2,0,0);
	inverseMatrix.setValueOn(2,1,(2.0/3.0));
	inverseMatrix.setValueOn(2,2,1);
	inverseMatrix.setValueOn(2,3,1);

	inverseMatrix.setValueOn(3,0,6);
	inverseMatrix.setValueOn(3,1,(11.0/3.0));
	inverseMatrix.setValueOn(3,2,2);
	inverseMatrix.setValueOn(3,3,1);

	return inverseMatrix;
}
