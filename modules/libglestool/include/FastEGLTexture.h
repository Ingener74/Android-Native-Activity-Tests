/*
 * FastEGLTexture.h
 *
 *  Created on: 20.02.2013
 *      Author: pavel
 */

#ifndef FASTEGLTEXTURE_H_
#define FASTEGLTEXTURE_H_

#include <dlfcn.h>

#include <opencv2/core/core.hpp>
#include <android_native_app_glue.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "ITexture.h"

#include "AndroidGraphicBuffer.h"

#include "tools.h"

using namespace cv;

#define LOGI_FET(...){ LOGI("FastEGLTexture", __VA_ARGS__); }
#define LOGE_FET(...){ LOGE("FastEGLTexture", __VA_ARGS__); }
#define LOGW_FET(...){ LOGW("FastEGLTexture", __VA_ARGS__); }

class FastEGLTexture: public ITexture{
public:
	typedef enum{
		FEGL_TEXTURE_FORMAT_RGBA8888,
		FEGL_TEXTURE_FORMAT_RGB565
	} FEGL_TEXTURE_FORMAT ;
	typedef enum{
		IMAGE_FORMAT_RGBA8888,
		IMAGE_FORMAT_RGB565,
		IMAGE_FORMAT_I8,
		IMAGE_FORMAT_D16,
		IMAGE_FORMAT_RGB888,
		IMAGE_FORMAT_END
	} IMAGE_FORMAT ;

	FastEGLTexture( void* data, uint32_t h, uint32_t w,
			IMAGE_FORMAT inputImageFormat, android_app* application,
			EGLDisplay disp, FEGL_TEXTURE_FORMAT fastTextureFormat );

	virtual ~FastEGLTexture();

	void bind();

	bool isError(){
		return _isError;
	}

	void updatePart( void* data, uint32_t h, uint32_t w, IMAGE_FORMAT format );

private:
	/*
	 * data
	 */
	bool                     _isError;
	GLuint                   _id;
	EGLImageKHR              _eglImage;
	EGLDisplay               _display;
	AndroidGraphicBuffer*    _graphicBuffer;
	FEGL_TEXTURE_FORMAT  _textureFormat;

	uint32_t                 _width;
	uint32_t                 _height;

	/*
	 * constants
	 */
	static const uint8_t     _depthNormalization = 5;
	static const uint8_t     _steps[];
	static const char*       _imageFormats[];
	static const char*       _textureFormats[];

	/*
	 * methods
	 */
	bool copy_pixel(
			void* src, uint32_t sh, uint32_t sw, uint8_t src_format,
			void* dst, uint32_t dh, uint32_t dw, uint8_t dst_format);
};

#endif /* FASTEGLTEXTURE_H_ */
