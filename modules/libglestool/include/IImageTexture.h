/*
 * IImageTexture.h
 *
 *  Created on: 08.03.2013
 *      Author: pavel
 */
#ifndef IIMAGETEXTURE_H_
#define IIMAGETEXTURE_H_

#include "opencv2/core/core.hpp"

#include "ITexture.h"

using namespace cv;

class IImageTexture: public ITexture{
public:
	IImageTexture(){}
	virtual ~IImageTexture(){}

	virtual void updatePart( Mat im ) = 0;
};

#endif /* IIMAGETEXTURE_H_ */
