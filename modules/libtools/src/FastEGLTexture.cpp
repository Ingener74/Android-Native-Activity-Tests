/*
 * FastEGLTexture.cpp
 *
 *  Created on: 20.02.2013
 *      Author: pavel
 */

#include "FastEGLTexture.h"

const uint8_t FastEGLTexture::_steps[] = {
		4,
		2,
		1,
		2,
		3,
};
const char* FastEGLTexture::_imageFormats[] = {
		"IMAGE_FORMAT_RGBA8888",
		"IMAGE_FORMAT_RGB565",
		"IMAGE_FORMAT_I8",
		"IMAGE_FORMAT_D16",
		"IMAGE_FORMAT_RGB888",
};
const char* FastEGLTexture::_textureFormats[] = {
		"FEGL_TEXTURE_FORMAT_RGBA8888",
		"FEGL_TEXTURE_FORMAT_RGB565",
};

FastEGLTexture::FastEGLTexture( void* data, uint32_t h, uint32_t w,
			IMAGE_FORMAT inputImageFormat, android_app* application,
			EGLDisplay disp, FEGL_TEXTURE_FORMAT fastTextureFormat ):

				_isError(false),
				_id(0),
				_eglImage(EGL_NO_IMAGE_KHR),
				_display(disp),
				_graphicBuffer(NULL),
				_textureFormat(fastTextureFormat),
				_width(w),
				_height(h){

	if( disp != EGL_NO_DISPLAY && application && EGLDispatcher::isInit() ){

		uint32_t format = (fastTextureFormat == FEGL_TEXTURE_FORMAT_RGBA8888) ?
				AndroidGraphicBuffer::HAL_PIXEL_FORMAT_RGBX_8888 :
				AndroidGraphicBuffer::HAL_PIXEL_FORMAT_RGB_565;

		_graphicBuffer = new AndroidGraphicBuffer(w, h,
				AndroidGraphicBuffer::GRALLOC_USAGE_SW_WRITE_OFTEN|
				AndroidGraphicBuffer::GRALLOC_USAGE_HW_TEXTURE, format);

		if(_graphicBuffer){

			uint8_t* bits = NULL;

			_graphicBuffer->lock(AndroidGraphicBuffer::GRALLOC_USAGE_SW_WRITE_OFTEN,
					(uchar**)&bits);

			if(bits){
				copy_pixel(data, h, w, inputImageFormat, bits, h, w, fastTextureFormat);
			}else{
				LOGE_FET("bits is empty");
			}
			_graphicBuffer->unlock();

			EGLint attr[] = {
					EGL_IMAGE_PRESERVED_KHR, EGL_TRUE,
					EGL_NONE, EGL_NONE
			};
			_eglImage = EGLDispatcher::eglCreateImageKHR(disp, EGL_NO_CONTEXT,
					EGL_NATIVE_BUFFER_ANDROID,
					(EGLClientBuffer)_graphicBuffer->getNativeBuffer(),
					attr);
			if(_eglImage != EGL_NO_IMAGE_KHR){

				glGenTextures(1, &_id);
				glBindTexture(GL_TEXTURE_2D, _id);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

				EGLDispatcher::glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, _eglImage);
				if(eglGetError() != EGL_SUCCESS){
					LOGE_FET("glEGLImageTargetTexture2DOES ERROR");
					_isError = true;
				}else{
					LOGW_FET("glEGLImageTargetTexture2DOES SUCCESS");
					_isError = false;
				}

			}else{
				LOGE_FET("can't create khronos image");
			}

		}else{
			LOGE_FET("android graphic buffer is not alloc");
		}

	}else{
		LOGE_FET("fast texture constructor error: disp = %d, "
				"application = %d, egldisp is init = %d",
				disp, application, EGLDispatcher::isInit() );
	}
}

FastEGLTexture::~FastEGLTexture() {
	EGLDispatcher::eglDestroyImageKHR(_display, _eglImage);
	glDeleteTextures(1, &_id);
	delete _graphicBuffer; _graphicBuffer = 0;
}

void FastEGLTexture::bind(){
	glBindTexture(GL_TEXTURE_2D, _id);
}

void FastEGLTexture::updatePart( void* data, uint32_t h, uint32_t w, IMAGE_FORMAT format ){

	if( _graphicBuffer && !_isError && data && (format >= 0 && format < IMAGE_FORMAT_END) ){

		uchar* bits = NULL;
		_graphicBuffer->lock(AndroidGraphicBuffer::GRALLOC_USAGE_SW_WRITE_OFTEN, (uchar**)&bits);

		if(bits && w <= _width && h <= _height ){

			copy_pixel(
					data, h, w, format,
					bits, _height, _width, _textureFormat);

		}else{
			LOGE_FET("update part: im > texture");
		}
		_graphicBuffer->unlock();
	}else{
		LOGE_FET("update part: graphic buffer not ready: _gb = %d, is error = %d, data = %d", _graphicBuffer, _isError, data);
	}

}

bool FastEGLTexture::copy_pixel(
		void* src, uint32_t sh, uint32_t sw, uint8_t src_format,
		void* dst, uint32_t dh, uint32_t dw, uint8_t dst_format){

	if( src && sh && sw && (src_format >= 0 && src_format < IMAGE_FORMAT_END) &&
			dst && dh && dw && (dst_format >= 0 && dst_format < IMAGE_FORMAT_END) &&
			sh <= dh && sw <= dw ){

//		LOGI_FET("%s:%d-> %s:%d",
//				_imageFormats[src_format], _steps[src_format],
//				_imageFormats[dst_format], _steps[dst_format]);

		if( src_format == dst_format ){

			uint8_t* src_ = (uint8_t*)src;
			uint8_t* dst_ = (uint8_t*)dst;

			for( uint32_t i = 0; i < sh; ++i ){

				uint8_t step = _steps[dst_format];

				dst_ = (uint8_t*)dst + i*dw*step;

				for( uint32_t j = 0; j < sw; ++j ){
					for(uint8_t n = 0; n < step; ++n ) *dst_++ = *src_++;
				}
			}

		}else if( src_format == IMAGE_FORMAT_RGB888 && dst_format == IMAGE_FORMAT_RGBA8888 ){

			uint8_t* src_ = (uint8_t*)src;
			uint8_t* dst_ = (uint8_t*)dst;

			for( uint32_t i = 0; i < sh; ++i ){
				dst_ = (uint8_t*)dst + i*dw*_steps[dst_format];

				for( uint32_t j = 0; j < sw; ++j ){
					*dst_++ = *src_++;
					*dst_++ = *src_++;
					*dst_++ = *src_++;
					*dst_++ = 255;
				}
			}
		}else if( src_format == IMAGE_FORMAT_RGBA8888 && dst_format == IMAGE_FORMAT_RGB888 ){

			uint8_t* src_ = (uint8_t*)src;
			uint8_t* dst_ = (uint8_t*)dst;

			for( uint32_t i = 0; i < sh; ++i ){
				dst_ = (uint8_t*)dst + i*dw*_steps[dst_format];

				for( uint32_t j = 0; j < sw; ++j ){
					*dst_++ = *src_++;
					*dst_++ = *src_++;
					*dst_++ = *src_++;
					src_++;
				}
			}

		}else if( src_format == IMAGE_FORMAT_D16 && dst_format == IMAGE_FORMAT_RGB888 ){

			uint16_t* src_ = (uint16_t*)src;
			uint8_t* dst_ = (uint8_t*)dst;

			for( uint32_t i = 0; i < sh; ++i ){
				dst_ = (uint8_t*)dst + i*dw*_steps[dst_format];

				for( uint32_t j = 0; j < sw; ++j ){
					uint8_t c = *src_++ >> _depthNormalization;

					*dst_++ = c;
					*dst_++ = c;
					*dst_++ = c;
				}
			}

		}else if( src_format == IMAGE_FORMAT_D16 && dst_format == IMAGE_FORMAT_RGBA8888 ){

			uint16_t* src_ = (uint16_t*)src;
			uint8_t* dst_ = (uint8_t*)dst;

			for( uint32_t i = 0; i < sh; ++i ){
				dst_ = (uint8_t*)dst + i*dw*_steps[dst_format];

				for( uint32_t j = 0; j < sw; ++j ){
					uint8_t c = *src_++ >> _depthNormalization;

					*dst_++ = c;
					*dst_++ = c;
					*dst_++ = c;
					*dst_++ = 255;
				}
			}
		}else if(src_format == IMAGE_FORMAT_D16 && dst_format == IMAGE_FORMAT_RGB565 ){

			uint16_t* src_ = (uint16_t*)src;
			uint16_t* dst_ = (uint16_t*)dst;

			for( uint32_t i = 0; i < sh; ++i ){
				dst_ = (uint16_t*)dst + i*dw;

				for( uint32_t j = 0; j < sw; ++j ){
					uint16_t c = *src_++ >> _depthNormalization;
					*dst_++ = ((c >> 3) << 11) | ((c >> 2) << 5) | (c >> 3);
				}
			}
		}else if(src_format == IMAGE_FORMAT_RGB888 && dst_format == IMAGE_FORMAT_RGB565 ){

			uint8_t* src_  = (uint8_t*)src;
			uint16_t* dst_ = (uint16_t*)dst;

			for( uint32_t i = 0; i < sh; ++i ){
				dst_ = (uint16_t*)dst + i*dw;
				for( uint32_t j = 0; j < sw; ++j ){

					uint16_t r = (*src_++ >> 3) << 11;
					uint16_t g = (*src_++ >> 2) << 5;
					uint16_t b = (*src_++ >> 3);

					*dst_++ = r | g | b;
				}
			}
		}else if(src_format == IMAGE_FORMAT_RGBA8888 && dst_format == IMAGE_FORMAT_RGB565 ){
			uint8_t* src_  = (uint8_t*)src;
			uint16_t* dst_ = (uint16_t*)dst;

			for( uint32_t i = 0; i < sh; ++i ){
				dst_ = (uint16_t*)dst + i*dw;
				for( uint32_t j = 0; j < sw; ++j ){

					uint16_t r = (*src_++ >> 3) << 11;
					uint16_t g = (*src_++ >> 2) << 5;
					uint16_t b = (*src_++ >> 3);
					src_++;

					*dst_++ = r | g | b;
				}
			}
		}

		return true;
	}else{
		return false;
	}
}









