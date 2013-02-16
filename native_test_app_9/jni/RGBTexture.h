/*
 * RGBTexture.h
 *
 *  Created on: 16.02.2013
 *      Author: pavel
 */

#ifndef RGBTEXTURE_H_
#define RGBTEXTURE_H_

#include <GLES/gl.h>
#include <GLES/glext.h>
#include <GLES/glplatform.h>

#include <opencv2/core/core.hpp>

#include "ITexture.h"
#include "HTATools.h"

using namespace cv;

class RGBTexture: public ITexture {
public:
	virtual ~RGBTexture();
	RGBTexture( const Mat& image );

	void update( const Mat& );
	void bind();

private:
	GLuint _id;
};

#endif /* RGBTEXTURE_H_ */
