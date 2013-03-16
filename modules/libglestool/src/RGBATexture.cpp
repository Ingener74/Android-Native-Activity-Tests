/*
 * RGBATexture.cpp
 *
 *  Created on: 27.02.2013
 *      Author: pavel
 */

#include "RGBATexture.h"

RGBATexture::RGBATexture(Mat im) :
		_id(0), _w(im.cols), _h(im.rows) {
	glGenTextures(1, &_id);
	Tools::glCheck("glGenTextures");
	glBindTexture(GL_TEXTURE_2D, _id);
	Tools::glCheck("glBindTexture");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _w, _h, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, im.data);
	Tools::glCheck("glTexImage2D");
}

RGBATexture::~RGBATexture() {
	glDeleteTextures(1, &_id);
	Tools::glCheck("glDeleteTextures");
}

void RGBATexture::bind() {
	glBindTexture(GL_TEXTURE_2D, _id);
	Tools::glCheck("glBindTexture");
}

void RGBATexture::updatePart(Mat im) {
	glBindTexture(GL_TEXTURE_2D, _id);
	Tools::glCheck("glBindTexture");
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, im.cols, im.rows, GL_RGBA,
			GL_UNSIGNED_BYTE, im.data);
	Tools::glCheck("glTexSubImage2D");
}
