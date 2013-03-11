/*
 * AndroidGraphicBuffer.cpp
 *
 *  Created on: 03.03.2013
 *      Author: pavel
 */

#include "AndroidGraphicBuffer.h"

const uint32_t AndroidGraphicBufferSize = 1024;

AndroidGraphicBuffer::AndroidGraphicBuffer(
		uint32_t width, uint32_t height, uint32_t usage, uint32_t format ):
				_isError(false), _instance(NULL), _usage(usage) {

	if(EGLDispatcher::isInit()){
		_instance = new uint8_t[AndroidGraphicBufferSize];
		if(_instance){
			uint8_t* p = _instance;
			for( int32_t i = 0; i < AndroidGraphicBufferSize; ++i )
				*p++ = 0;
		}
		if(_instance){

			EGLDispatcher::GraphicBufferCtor(_instance, width, height, format, usage);
			LOGI_AGB("graphic buffer instance created and constructed");

			_isError = false;

		}else{
			LOGE_AGB("have not memory for graphic buffer instance");
			_isError = true;
		}
	}else{
		LOGE_AGB("egl function not allowed");
		_isError = true;
	}
}

AndroidGraphicBuffer::~AndroidGraphicBuffer() {
	if(!_isError){
		EGLDispatcher::GraphicBufferDtor(_instance);
	}
	if(_instance)
		delete [] _instance;
}

int32_t AndroidGraphicBuffer::lock( uint32_t usage, uint8_t** bits ){
	if(!_isError){
		return EGLDispatcher::GraphicBufferLock(_instance, _usage, bits);
	}else{
		LOGE_AGB("Android Graphic Buffer error in lock");
		return false;
	}
}

int32_t AndroidGraphicBuffer::unlock(){
	if(!_isError){
		return EGLDispatcher::GraphicBufferUnlock(_instance);
	}else{
		return false;
	}
}

void* AndroidGraphicBuffer::getNativeBuffer(){
	if(!_isError){
		return EGLDispatcher::GraphicBufferGetNativeBuffer(_instance);
	}else{
		return NULL;
	}
}






