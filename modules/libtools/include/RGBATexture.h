/*
 * RGBATexture.h
 *
 *  Created on: 27.02.2013
 *      Author: pavel
 */

#ifndef RGBATEXTURE_H_
#define RGBATEXTURE_H_

#include <opencv2/core/core.hpp>

#include "IImageTexture.h"
#include "tools.h"

using namespace cv;

#define LOGI_RGBA(...){ LOGI("RGBATexture", __VA_ARGS__); }
#define LOGE_RGBA(...){ LOGE("RGBATexture", __VA_ARGS__); }

class RGBATexture: public ITexture{
public:
	RGBATexture( Mat im );
	virtual ~RGBATexture();

	void updatePart( Mat im );

	void bind();

private:
	GLuint _id;
	GLuint _w, _h;
};

#endif /* RGBATEXTURE_H_ */
