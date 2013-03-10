/*
 * ITexture.h
 *
 *  Created on: 16.02.2013
 *      Author: pavel
 */

#ifndef ITEXTURE_H_
#define ITEXTURE_H_

class ITexture {
public:
	virtual ~ITexture(){}

	virtual void bind() = 0;
};

#endif /* ITEXTURE_H_ */
