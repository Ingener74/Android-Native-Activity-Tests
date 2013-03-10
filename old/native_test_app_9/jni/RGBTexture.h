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
#include "tools.h"

using namespace cv;

class RGBTexture: public ITexture {
public:
	virtual ~RGBTexture();
	RGBTexture( const Mat& image );

	void updateAll( const Mat& im );
	void updatePart( const Mat& im );
	void bind();

private:
	GLuint _id;
};

#endif /* RGBTEXTURE_H_ */
