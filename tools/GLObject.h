/*
 * GLObject.h
 *
 *  Created on: 16.02.2013
 *      Author: pavel
 */

#ifndef GLOBJECT_H_
#define GLOBJECT_H_

class GLObject {
public:
	virtual ~GLObject(){}

	virtual void draw() = 0;
};

#endif /* GLOBJECT_H_ */
