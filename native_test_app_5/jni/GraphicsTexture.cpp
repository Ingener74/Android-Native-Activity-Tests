/*
 * GraphicsTexture.cpp
 *
 *  Created on: 27.01.2013
 *      Author: pavel
 */

#include "GraphicsTexture.h"
#include "Log.h"

namespace smallarsdk {

GraphicsTexture::GraphicsTexture(android_app* application, const char* path):
	_resource(application, path),
	_textureID(0),
	_width(0), _height(0),
	_format(0){
}

GraphicsTexture::~GraphicsTexture(){
}

const char* GraphicsTexture::getPath(){ return _resource.getPath(); }
int32_t GraphicsTexture::getWidth() const { return _width; }
int32_t GraphicsTexture::getHeight() const { return _height; }

uint8_t* GraphicsTexture::loadImage(){
	png_byte     header[8];
	png_structp  pngPtr = NULL;
	png_infop    infoPtr = NULL;
	png_byte*    imageBuffer = NULL;
	png_bytep*   rowPtr = NULL;
	png_int_32   rowSize;
	bool         transparency;

	if(_resource.open() != STATUS_OK ) goto ERROR;
	if(_resource.read(header, sizeof(header)) != STATUS_OK) goto ERROR;
	if(png_sig_cmp(header, 0, 8) != 0) goto ERROR;

	pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if(!pngPtr) goto ERROR;

	infoPtr = png_create_info_struct(pngPtr);
	if(!infoPtr) goto ERROR;

	png_set_read_fn(pngPtr, &_resource, callback_read);
	if( setjmp(png_jmpbuf(pngPtr))) goto ERROR;

	png_set_sig_bytes(pngPtr, 8);

	png_read_info(pngPtr, infoPtr);
//	png_read_update_info(pngPtr, infoPtr);

	png_int_32 depth, colorType;
	png_uint_32 width, height;

	png_get_IHDR(pngPtr, infoPtr, &width, &height, &depth, &colorType,
			NULL, NULL, NULL);

	_width = width;
	_height = height;

	transparency = false;
	if(png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS)){
		png_set_tRNS_to_alpha(pngPtr);
		transparency = true;
		goto ERROR;
	}

	if(depth < 8){
		png_set_packing(pngPtr);
	}else if(depth == 16){
		png_set_strip_16(pngPtr);
	}

	switch(colorType){
	case PNG_COLOR_TYPE_PALETTE:{
		png_set_palette_to_rgb(pngPtr);
		_format = transparency ? GL_RGBA : GL_RGB;
		break;
	}
	case PNG_COLOR_TYPE_RGB:{
		_format = transparency ? GL_RGBA : GL_RGB;
		break;
	}
	case PNG_COLOR_TYPE_RGBA:{
		_format = GL_RGBA;
		break;
	}
	case PNG_COLOR_TYPE_GRAY:{
		png_set_expand_gray_1_2_4_to_8(pngPtr);
		_format = transparency ? GL_LUMINANCE_ALPHA : GL_LUMINANCE;
		break;
	}
	case PNG_COLOR_TYPE_GA:{
		png_set_expand_gray_1_2_4_to_8(pngPtr);
		_format = GL_LUMINANCE_ALPHA;
		break;
	}
	}
	png_read_update_info(pngPtr, infoPtr);

	rowSize = png_get_rowbytes(pngPtr, infoPtr);
	if(rowSize <= 0) goto ERROR;

	imageBuffer = new png_byte[rowSize * height];
	if(!imageBuffer) goto ERROR;

	rowPtr = new png_bytep[height];
	if(!rowPtr){
		for(int32_t i = 0; i < height; ++i ){
			rowPtr[height - (i + 1)] = imageBuffer + i * rowSize;
		}
	}

	png_read_image(pngPtr, rowPtr);

	_resource.close();
	png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
	delete [] rowPtr;
	return imageBuffer;

	ERROR:
	Log::error("Error while reading PNG file");
	_resource.close();
	delete [] rowPtr; delete [] imageBuffer;
	if(pngPtr != NULL){
		png_infop* infoPtrP = infoPtr != NULL ? &infoPtr : NULL;
		png_destroy_read_struct(&pngPtr, infoPtrP, NULL);
	}
	return NULL;
}

void GraphicsTexture::callback_read( png_structp png, png_bytep data, png_size_t size ){
	Resources& reader = *((Resources*)png_get_io_ptr(png));
	if(reader.read(data, size) != STATUS_OK){
		reader.close();
		png_error(png, "Error while reading PNG file");
	}
}

status GraphicsTexture::load(){
	uint8_t* imageBuffer = loadImage();

	if(imageBuffer == NULL){
		return STATUS_KO;
	}

	GLenum errorResult;
	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(
			GL_TEXTURE_2D,
			0,
			_format,
			_width, _height,
			0, _format,
			GL_UNSIGNED_BYTE, imageBuffer);

	delete [] imageBuffer;
	if(glGetError() != GL_NO_ERROR){
		Log::error("Error loading texture into OpenGL");
		unload();
		return STATUS_KO;
	}
	return STATUS_OK;
}

void GraphicsTexture::unload(){
	if(_textureID != 0){
		glDeleteTextures(1, &_textureID);
		_textureID = 0;
	}
	_width  = 0;
	_height = 0;
	_format = 0;
}

void GraphicsTexture::apply(){
	glActiveTexture(GL_TEXTURE0 );
	glBindTexture(GL_TEXTURE_2D, _textureID);
}

} /* namespace smallarsdk */








