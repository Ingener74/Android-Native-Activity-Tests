/*
 * Triangle.h
 *
 *  Created on: 14.02.2013
 *      Author: pavel
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Point.h"

namespace go {

class Triangle: public IGraphicsObject {
public:
	Triangle( Point p1, Point p2, Point p3 );
	virtual ~Triangle();

	virtual void draw();

protected:
	Point _points[3];
};

} /* namespace go */
#endif /* TRIANGLE_H_ */
