/*
 * GraphicsTexture.h
 *
 *  Created on: 27.01.2013
 *      Author: pavel
 */

#ifndef GRAPHICSTEXTURE_H_
#define GRAPHICSTEXTURE_H_

#include <GLES/gl.h>
#include <png.h>
#include <android_native_app_glue.h>

#include "Context.h"
#include "Types.hpp"
#include "Resources.h"

namespace smallarsdk {

class GraphicsTexture {
public:
	GraphicsTexture(android_app* application, const char* path);
	virtual ~GraphicsTexture();

	int32_t getHeight() const ;
	int32_t getWidth() const ;

	status load();
	void unload();
	void apply();

protected:
	uint8_t* loadImage();

private:
	static void callback_read( png_structp struct_, png_bytep data, png_size_t size );

private:
	Resources _resource;
	GLuint    _textureID;
	int32_t   _width, _height;
	GLint     _format;
};

} /* namespace smallarsdk */
#endif /* GRAPHICSTEXTURE_H_ */
