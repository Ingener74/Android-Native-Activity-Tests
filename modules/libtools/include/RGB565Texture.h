/*
 * RGB565Texture.h
 *
 *  Created on: 22.02.2013
 *      Author: pavel
 */

#ifndef RGB565TEXTURE_H_
#define RGB565TEXTURE_H_

#include <GLES/gl.h>

#include <opencv2/core/core.hpp>

#include "ITexture.h"
#include "tools.h"

using namespace cv;

class RGB565Texture: public ITexture {
public:
	RGB565Texture( Mat im );
	virtual ~RGB565Texture();

	void updateAll( Mat im );
	void updatePart( Mat im );
	void bind();

	static void rgb888_565( const Mat in, Mat out );

protected:
	GLuint _id;
	Mat    _im;
};

#endif /* RGB565TEXTURE_H_ */
