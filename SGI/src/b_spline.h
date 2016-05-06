/*
 * b_spline.h
 *
 *  Created on: 5 de mai de 2016
 *      Author: plab
 */

#ifndef SRC_B_SPLINE_H_
#define SRC_B_SPLINE_H_

#include <cmath>

#include "geometric_object.hpp"

class BSpline : public GeometricObject {
public:
	BSpline(string name, vector<Coordinate> controlPoints, double step);
	virtual ~BSpline();

	virtual void applyClipping();

private:
	void _generatePoints(vector<Coordinate> controlPoints, double step);

	Matrix<4,1,double> _buildGeometryMatrix(vector<Coordinate> controlPoints, int startIndex);
	Matrix<4,4,double> _buildDiffMatrix(double step);
	Matrix<4,4, double> _buildInverseSplineMatrix();
};

#endif /* SRC_B_SPLINE_H_ */
