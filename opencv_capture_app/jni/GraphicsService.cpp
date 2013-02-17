/*
 * GraphicsService.cpp
 *
 *  Created on: 03.02.2013
 *      Author: pavel
 */

#include "GraphicsService.h"

namespace native_test_app_8 {

GraphicsService::GraphicsService( android_app* application ):
	_display(EGL_NO_DISPLAY),
	_context(EGL_NO_CONTEXT),
	_surface(EGL_NO_SURFACE),
	_width(0), _height(0){

	if(application != NULL){
		init(application);
	}

}

void GraphicsService::init( android_app* application ){
	LOGI("GraphicsService", "init begin");

	const EGLint attribs[] = {
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_BLUE_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_RED_SIZE, 8,
			EGL_DEPTH_SIZE, 8,
			EGL_NONE
	};

	EGLint dummy, format;
	EGLint numConf;
	EGLConfig config;

	_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	eglInitialize(_display, 0, 0);

	eglChooseConfig(_display, attribs, &config, 1, &numConf);

	eglGetConfigAttrib(_display, config, EGL_NATIVE_VISUAL_ID, &format);

	ANativeWindow_setBuffersGeometry(application->window, 0, 0, format);

	_surface = eglCreateWindowSurface(_display, config, application->window, NULL);
	_context = eglCreateContext(_display, config, NULL, NULL);

	if(eglMakeCurrent(_display, _surface, _surface, _context) == EGL_FALSE){
		LOGE("GraphicsService", "Unable to eglMakeCurrent");
		return;
	}
	eglQuerySurface(_display, _surface, EGL_WIDTH, &_width);
	eglQuerySurface(_display, _surface, EGL_HEIGHT, &_height);

	const double dim_d = 1000.0; // depth dimension
	const double dim_w = 864, dim_h = 480;

	const double aspect = _height / double(_width);
	glViewport(0, 0, _width, _height);
	LOGI("GraphicsService", "h = %d, w = %d", _height, _width);

	glOrthof(0.f, dim_w, -dim_h, 0, - dim_d * 100.f, dim_d * 100.f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	LOGI("GraphicsService", "init end");
}

void GraphicsService::deinit(){
	LOGI("GraphicsService", "deinit begin");

	if(_display != EGL_NO_DISPLAY){
		eglMakeCurrent(_display, _surface, _surface, _context);
		if(_context != EGL_NO_CONTEXT){
			eglDestroyContext(_display, _context);
		}
		if(_surface != EGL_NO_SURFACE){
			eglDestroySurface(_display, _surface);
		}
		eglTerminate(_display);
	}
	_display = EGL_NO_DISPLAY;
	_context = EGL_NO_CONTEXT;
	_surface = EGL_NO_SURFACE;

	LOGI("GraphicsService", "deinit end");
}

GraphicsService::~GraphicsService() {
	deinit();
}

} /* namespace native_test_app_7 */
