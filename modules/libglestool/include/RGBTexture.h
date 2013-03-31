/*
 * RGBTexture.h
 *
 *  Created on: 16.02.2013
 *      Author: pavel
 */

#ifndef RGBTEXTURE_H_
#define RGBTEXTURE_H_

#include <GLES2/gl2.h>

#include <opencv2/core/core.hpp>

#include "IImageTexture.h"
#include "tools.h"

using namespace cv;

class RGBTexture: public IImageTexture{
public:
	virtual ~RGBTexture();
	RGBTexture( Mat image, GLuint _shaderTextureSampleID = -1 );

	void updatePart( Mat image );
	void bind();

private:
	GLuint _id;
	GLuint _shaderUniformID;

	GLuint upperPowerOfTwo( GLuint v );
};

#endif /* RGBTEXTURE_H_ */
