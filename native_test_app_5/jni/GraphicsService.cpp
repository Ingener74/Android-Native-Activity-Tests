/*
 * GraphicsService.cpp
 *
 *  Created on: 27.01.2013
 *      Author: pavel
 */

#include "GraphicsService.h"
#include "Log.h"

#include <GLES/gl.h>
#include <GLES/glext.h>

namespace smallarsdk {

GraphicsService::GraphicsService(
		android_app* application,
		TimeService* timeService ):
			_application(application),
			_timeService(timeService),
			_width(0), _height(0),
			_display(EGL_NO_DISPLAY),
			_surface(EGL_NO_SURFACE),
			_context(EGL_NO_CONTEXT){
}

const char* GraphicsService::getPath(){
//	return _resource.getPath();
	return (const char*)0;
}
const int32_t& GraphicsService::getWidth() const {
	 return _width;
}
const int32_t& GraphicsService::getHeight() const {
	return _height;
}

status GraphicsService::start(){
	EGLint format, numConfigs, errorResult;
	EGLConfig config;
	const EGLint attributes[] = {
			EGL_RENDERABLE_TYPE,
			EGL_OPENGL_ES_BIT,
			EGL_BLUE_SIZE,  5,
			EGL_GREEN_SIZE, 6,
			EGL_RED_SIZE,   5,
			EGL_SURFACE_TYPE,
			EGL_WINDOW_BIT,
			EGL_NONE
	};

	_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if(_display == EGL_NO_DISPLAY) goto ERROR;
	if(!eglInitialize(_display, NULL, NULL)) goto ERROR;

	if(!eglChooseConfig(_display, attributes, &config, 1, &numConfigs) || (numConfigs <= 0)) goto ERROR;

	if(!eglGetConfigAttrib(_display, config, EGL_NATIVE_VISUAL_ID, &format)) goto ERROR;

	ANativeWindow_setBuffersGeometry(_application->window, 0, 0, format);

	_surface = eglCreateWindowSurface(_display, config, _application->window, NULL);
	if(_surface == EGL_NO_SURFACE) goto ERROR;

	_context = eglCreateContext(_display, config, EGL_NO_CONTEXT, NULL);
	if(_context == EGL_NO_CONTEXT) goto ERROR;

	if( !eglMakeCurrent(_display, _surface, _surface, _context) ||
			!eglQuerySurface(_display, _surface, EGL_WIDTH, &_width) ||
			!eglQuerySurface(_display, _surface, EGL_HEIGHT, &_height) ||
			(_width <= 0) || (_height <= 0)) goto ERROR;

	return STATUS_OK;

	ERROR:
	Log::error("Error while starting GraphicsService");
	stop();
	return STATUS_KO;
}

void GraphicsService::stop(){
	if(_display != EGL_NO_DISPLAY){
		eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		if(_context != EGL_NO_CONTEXT){
			eglDestroyContext(_display, _context);
			_context = EGL_NO_CONTEXT;
		}
		if(_surface != EGL_NO_SURFACE){
			eglDestroySurface(_display, _surface);
		}
		eglTerminate(_display);
		_display = EGL_NO_DISPLAY;
	}
}

status GraphicsService::update(){
	float timeStep = _timeService->elapsed();

	static float clearColor = 0.0f;
	static bool  dir = true;
	const float dSC = 0.25f;

	float dC = 0.0f;

	if(dir){
		dC = dSC;
	}else{
		dC = -dSC;
	}
	clearColor += timeStep * dC;

	Log::info("clear color = %f", clearColor);

	if(clearColor > 0.9 && dir ){
		Log::warn("dir changed false");
		dir = false;

	}else if(clearColor < 0.1 && !dir ){
		Log::warn("dir changed true");
		dir = true;
	}

	glClearColor(0.3f, clearColor, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if(eglSwapBuffers(_display, _surface) != EGL_TRUE ){
		Log::error("Error %d swapping buffers.", eglGetError());
		return STATUS_KO;
	}
	return STATUS_OK;
}


} /* namespace smallarsdk */








