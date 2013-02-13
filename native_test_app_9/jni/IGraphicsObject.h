/*
 * IGraphicsObject.h
 *
 *  Created on: Feb 14, 2013
 *      Author: ingener
 */

#ifndef IGRAPHICSOBJECT_H_
#define IGRAPHICSOBJECT_H_

namespace go {

class IGraphicsObject {
public:
	virtual ~IGraphicsObject(){}

	virtual void draw() = 0;
};

} /* namespace graphics_objects */
#endif /* IGRAPHICSOBJECT_H_ */
