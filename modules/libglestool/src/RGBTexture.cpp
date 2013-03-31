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

RGBTexture::RGBTexture( Mat im, GLuint _shaderTextureSampleID ): _id(0),
		_shaderUniformID(_shaderTextureSampleID){
	glGenTextures(1, &_id);

	glBindTexture(GL_TEXTURE_2D, _id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im.cols, im.rows, 0, GL_RGB,
			GL_UNSIGNED_BYTE, im.data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void RGBTexture::updatePart( Mat im ) {
	glBindTexture(GL_TEXTURE_2D, _id);

	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, im.cols, im.rows, GL_RGB,
			GL_UNSIGNED_BYTE, im.data);
}

void RGBTexture::bind() {
	if(_shaderUniformID != -1)
		glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _id);
	if(_shaderUniformID != -1)
		glUniform1i(_shaderUniformID, 0);
}

GLuint RGBTexture::upperPowerOfTwo( GLuint v ){
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}
