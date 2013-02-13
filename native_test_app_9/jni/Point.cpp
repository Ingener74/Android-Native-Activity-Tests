/*
 * Point.cpp
 *
 *  Created on: Feb 14, 2013
 *      Author: ingener
 */

#include "Point.h"

namespace go {

Point::Point(GLfloat x, GLfloat y, GLfloat z):
	_x(x), _y(y), _z(z){

}

Point::~Point() {
}

void Point::draw(){
	glEnableClientState(GL_ARRAY_BUFFER);
	glVertexPointer(3, GL_FLOAT, 0, _v);
	glDrawArrays(GL_POINTS, 0, 1);
	glDisableClientState(GL_ARRAY_BUFFER);
}

} /* namespace graphics_objects */
