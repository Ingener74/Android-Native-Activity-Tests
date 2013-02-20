/*
 * IObject.h
 *
 *  Created on: 17.02.2013
 *      Author: pavel
 */

#ifndef IOBJECT_H_
#define IOBJECT_H_

class IObject {
public:
	IObject(){}
	virtual ~IObject(){}

	virtual void draw() = 0;
};

#endif /* IOBJECT_H_ */
