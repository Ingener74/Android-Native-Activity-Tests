/*
 * RGB565Texture.cpp
 *
 *  Created on: 22.02.2013
 *      Author: pavel
 */

#include "RGB565Texture.h"

RGB565Texture::RGB565Texture( Mat im )
	: _id(0), _im(Mat(im.size(), CV_16U, Scalar(0))) {
	LOGI("RGB565Texture", "RGB565Texture create begin");

	rgb888_565(im, _im);
	LOGI("RGB565Texture", "888 -> 565 conv: %d x %d", _im.rows, _im.cols);

	glGenTextures(1, &_id);
	GLERR;
	LOGI("RGB565Texture", "RGB565Texture id = %d", _id);
	glBindTexture(GL_TEXTURE_2D, _id);
	GLERR;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _im.cols, _im.rows, 0, GL_RGB,
			GL_UNSIGNED_SHORT_5_6_5, _im.data);
	GLERR;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	LOGI("RGB565Texture", "RGB565Texture create end");
}

RGB565Texture::~RGB565Texture() {
}

void RGB565Texture::bind(){
	glBindTexture(GL_TEXTURE_2D, _id); GLERR;
}

void RGB565Texture::updateAll( Mat im ){
	rgb888_565(im, _im);
	LOGI("RGB565Texture", "RGB565Texture update begin");
	glBindTexture(GL_TEXTURE_2D, _id); GLERR;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _im.cols, _im.rows, 0, GL_RGB,
			GL_UNSIGNED_BYTE, _im.data); GLERR;
	LOGI("RGB565Texture", "RGB565Texture update end");
}

void RGB565Texture::updatePart( Mat im ){
	rgb888_565(im, _im);
	LOGI("RGB565Texture", "RGB565Texture update begin");
	glBindTexture(GL_TEXTURE_2D, _id); GLERR;

	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _im.cols, _im.rows, GL_RGB,
			GL_UNSIGNED_BYTE, _im.data); GLERR;
	LOGI("RGB565Texture", "RGB565Texture update end");
}

void RGB565Texture::rgb888_565( const Mat in, Mat out ){
	if( out.size() != in.size() )
		out = Mat(in.size(), CV_16U, Scalar());

	register uchar*    inp  = in.data;
	register uint16_t* outp = (uint16_t*)out.data;

	for( int32_t i = 0; i < in.rows * in.cols; ++i ){
		register uint16_t t =
				((*(inp + 0)&0xF8) << 8) |
				((*(inp + 1)&0xFC) << 3) |
				((*(inp + 2)&0xF8) >> 3);

		*outp++ = t;
		inp += 3;
	}
}
