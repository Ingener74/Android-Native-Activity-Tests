/*
 * Point.h
 *
 *  Created on: Feb 14, 2013
 *      Author: ingener
 */

#ifndef POINT_H_
#define POINT_H_

#include "GLES/gl.h"
#include "IGraphicsObject.h"

namespace go {

class Point: public IGraphicsObject{
public:
	Point( GLfloat x = 0.f, GLfloat y = 0.f, GLfloat z = 0.f);
	virtual ~Point();

	virtual void draw();

protected:
	union{
		struct{
			GLfloat _x;
			GLfloat _y;
			GLfloat _z;
		};
		GLfloat _v[3];
	};
};

} /* namespace graphics_objects */
#endif /* POINT_H_ */
