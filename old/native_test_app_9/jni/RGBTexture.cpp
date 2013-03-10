/*
 * RGBTexture.cpp
 *
 *  Created on: 16.02.2013
 *      Author: pavel
 */

#include "RGBTexture.h"

RGBTexture::~RGBTexture() {
	glDeleteTextures(1, &_id);
}

RGBTexture::RGBTexture(const Mat& im) {
	LOGI("RGBTexture", "RGBTexture create begin");

	glGenTextures(1, &_id);
	GLERR;
	LOGI("RGBTexture", "RGBTexture id = %d", _id);
	glBindTexture(GL_TEXTURE_2D, _id);
	GLERR;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im.cols, im.rows, 0, GL_RGB,
			GL_UNSIGNED_BYTE, im.data);
	GLERR;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	LOGI("RGBTexture", "RGBTexture create end");
}

void RGBTexture::updateAll( const Mat& im ){
	LOGI("RGBTexture", "RGBTexture update begin");
	glBindTexture(GL_TEXTURE_2D, _id);
	GLERR

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im.cols, im.rows, 0, GL_RGB,
			GL_UNSIGNED_BYTE, im.data);
	GLERR;
	LOGI("RGBTexture", "RGBTexture update end");
}

void RGBTexture::updatePart(const Mat& im) {
	LOGI("RGBTexture", "RGBTexture update begin");
	glBindTexture(GL_TEXTURE_2D, _id);
	GLERR

	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, im.cols, im.rows, GL_RGB,
			GL_UNSIGNED_BYTE, im.data); GLERR;
	GLERR;
	LOGI("RGBTexture", "RGBTexture update end");
}

void RGBTexture::bind() {
	glBindTexture(GL_TEXTURE_2D, _id);
	GLERR
}
