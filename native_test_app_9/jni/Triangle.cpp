/*
 * Triangle.cpp
 *
 *  Created on: 14.02.2013
 *      Author: pavel
 */

#include "Triangle.h"

namespace go {

Triangle::Triangle( Point p1, Point p2, Point p3 ) {
	_points[0] = p1;
	_points[1] = p2;
	_points[2] = p3;
}

Triangle::~Triangle() {
}

void Triangle::draw(){
	GLfloat points[] = {
			_points[0].getX(), _points[0].getY(), _points[0].getZ(),
			_points[1].getX(), _points[1].getY(), _points[1].getZ(),
			_points[2].getX(), _points[2].getY(), _points[2].getZ(),
	};

	glEnableClientState(GL_ARRAY_BUFFER);
	glVertexPointer(9, GL_FLOAT, 0, points);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableClientState(GL_ARRAY_BUFFER);
}

} /* namespace go */
