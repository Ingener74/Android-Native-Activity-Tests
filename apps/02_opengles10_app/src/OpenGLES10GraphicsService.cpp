/*
 * OpenGLES10GraphicsService.cpp
 *
 *  Created on: 10.03.2013
 *      Author: pavel
 */

#include "OpenGLES10GraphicsService.h"

const char* tex_file = "/sdcard/textures/brickwall.png";

const GLfloat s = 50.f;
GLfloat cube1[] = {
		s, -s, s,
		s, s, s,
		s, s, -s,
		s, -s, -s
};
GLfloat cube2[] = {
		-s, -s, s,
		s, -s, s,
		s, -s, -s,
		-s, -s, -s
};
GLfloat cube3[] = {
		s, s, s,
		-s, s, s,
		-s, s, -s,
		s, s, -s
};
GLfloat cube4[] = {
		-s, s, s,
		-s, -s, s,
		-s, -s, -s,
		-s, s, -s
};
GLfloat cube5[] = {
		-s, -s, s,
		-s, s, s,
		s, s, s,
		s, -s, s,
};
GLfloat cube6[] = {
		s, -s, -s,
		s, s, -s,
		-s, s, -s,
		-s, -s, -s
};

GLfloat texcoords[] = {
		0.f, 0.f,
		1.f, 0.f,
		1.f, 1.f,
		0.f, 1.f
};
GLfloat colors[] = {
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
};
GLushort indexes[] = {
		0, 1, 2,
		2, 3, 0
};

OpenGLES10GraphicsService::OpenGLES10GraphicsService():
		_display(EGL_NO_DISPLAY), _context(EGL_NO_CONTEXT),
		_surface(EGL_NO_SURFACE), _width(0), _height(0), _mt(NULL), _isInit(false){
}

OpenGLES10GraphicsService::~OpenGLES10GraphicsService() {
}

OpenGLES10GraphicsService::STATUS OpenGLES10GraphicsService::init( android_app* app ){
	_application = app;

	const EGLint attribs[] = {
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_BLUE_SIZE,  8,
			EGL_GREEN_SIZE, 8,
			EGL_RED_SIZE,   8,
			EGL_DEPTH_SIZE, 8,
			EGL_NONE
	};

	EGLint format, numConf;
	EGLConfig config;

	_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	eglInitialize(_display, 0, 0);

	eglChooseConfig(_display, attribs, &config, 1, &numConf);

	eglGetConfigAttrib(_display, config, EGL_NATIVE_VISUAL_ID, &format);

	ANativeWindow_setBuffersGeometry(_application->window, 0, 0, format);

	_surface = eglCreateWindowSurface(_display, config, _application->window, NULL);
	_context = eglCreateContext(_display, config, NULL, NULL);

	if(eglMakeCurrent(_display, _surface, _surface, _context) == EGL_FALSE){
		LOGE_OGLES10GS("Unable to eglMakeCurrent");
		return STATUS_ERROR;
	}
	eglQuerySurface(_display, _surface, EGL_WIDTH, &_width);
	eglQuerySurface(_display, _surface, EGL_HEIGHT, &_height);

	const double dim = 200.0;
	const double aspect = _height / double(_width);
	glViewport(0, 0, _width, _height);
	LOGW_OGLES10GS("h = %d, w = %d", _height, _width);

	glOrthof(-dim, dim, -aspect*dim, aspect*dim, - dim * 100.f, dim * 100.f);

	Mat tex_im = imread(tex_file);
	if(!tex_im.empty()){
		cvtColor(tex_im, tex_im, CV_RGB2BGR);
		_mt = new RGBTexture(tex_im);
	}

	glEnable(GL_DEPTH_TEST);

	_tri[0] = new GLTriangle(_mt, cube1, texcoords, colors, indexes, 6);
	_tri[1] = new GLTriangle(_mt, cube2, texcoords, colors, indexes, 6);
	_tri[2] = new GLTriangle(_mt, cube3, texcoords, colors, indexes, 6);
	_tri[3] = new GLTriangle(_mt, cube4, texcoords, colors, indexes, 6);
	_tri[4] = new GLTriangle(_mt, cube5, texcoords, colors, indexes, 6);
	_tri[5] = new GLTriangle(_mt, cube6, texcoords, colors, indexes, 6);

	glTranslatef(0, 0, -200);

	_isInit = true;

	return STATUS_OK;
}

void OpenGLES10GraphicsService::deinit(){
	LOGI_OGLES10GS("deinit begin");

	delete _mt;
	for( int32_t i = 0; i < squares; ++i ){
		delete _tri[i];
	}

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

	LOGI_OGLES10GS("deinit end");
}

void OpenGLES10GraphicsService::draw(){

	glClearColor(0.f, 0.3f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);

	for( int32_t i = 0; i < squares; ++i )
		if(_tri[i])
			_tri[i]->draw();

	glRotatef(0.3f, 1.f, 0.f, 0.f);
	glRotatef(0.13f, 0.f, 1.f, 0.f);

	glDisable(GL_TEXTURE_2D);

	glFinish();
	eglSwapBuffers(_display, _surface);
}

void OpenGLES10GraphicsService::setImage( Mat image ){
}
