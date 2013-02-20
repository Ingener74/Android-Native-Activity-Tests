/*
 * OpenGLES100GraphicsService.cpp
 *
 *  Created on: Feb 18, 2013
 *      Author: ingener
 */

#include "OpenGLES100GraphicsService.h"

namespace opengles_test {

const string tex_file = "/sdcard/textures/brickwall.png";

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

OpenGLES100GraphicsService::OpenGLES100GraphicsService(): IGraphicsService(),
		_display(EGL_NO_DISPLAY), _context(EGL_NO_CONTEXT),
		_surface(EGL_NO_SURFACE), _width(0), _height(0),
		_mt(0){
	LOGI_OGLESS("OpenGLES100GraphicsService constructor begin");
	for( int32_t i = 0; i < squares; ++i ){
//		delete _tri[i];
		_tri[i] = 0;
	}
	LOGI_OGLESS("OpenGLES100GraphicsService constructor end");
}

OpenGLES100GraphicsService::~OpenGLES100GraphicsService() {
}

void OpenGLES100GraphicsService::draw(){

	glClearColor(0.f, 0.3f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);

	static bool trans = false;
	if( !trans ){
		glTranslatef(0, 0, -100);
		trans = true;
	}

	for( int32_t i = 0; i < squares; ++i )
		if(_tri[i])
			_tri[i]->draw();

	glRotatef(0.3f, 1.f, 0.f, 0.f);
	glRotatef(0.13f, 0.f, 1.f, 0.f);

	glDisable(GL_TEXTURE_2D);

	glFinish();
	eglSwapBuffers(_display, _surface);
}

IGraphicsService::STATUS OpenGLES100GraphicsService::init(
		android_app* application ){
	_application = application;

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
		LOGI_OGLESS("Unable to eglMakeCurrent");
		return IGraphicsService::STATUS_ERROR;
	}
	eglQuerySurface(_display, _surface, EGL_WIDTH, &_width);
	eglQuerySurface(_display, _surface, EGL_HEIGHT, &_height);

	const double dim = 200.0;
	const double aspect = _height / double(_width);
	glViewport(0, 0, _width, _height);
	LOGI_OGLESS("h = %d, w = %d", _height, _width);

	glOrthof(-dim, dim, -aspect*dim, aspect*dim, - dim * 100.f, dim * 100.f);
	LOGI_OGLESS("left = %f, right = %f, bottom = %f, top = %f, zNear = %f, "
			"zFar = %f",
			-dim, dim, -aspect*dim, aspect*dim, -dim, dim);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/*
	 * create objects
	 */

	Mat tex_im = imread(tex_file);
	if(!tex_im.empty()){
		cvtColor(tex_im, tex_im, CV_RGB2BGR);
		_mt = new RGBTexture(tex_im);
	}

	_tri[0] = new GLTriangle(_mt, cube1, texcoords, colors, indexes, 6);
	_tri[1] = new GLTriangle(_mt, cube2, texcoords, colors, indexes, 6);
	_tri[2] = new GLTriangle(_mt, cube3, texcoords, colors, indexes, 6);
	_tri[3] = new GLTriangle(_mt, cube4, texcoords, colors, indexes, 6);
	_tri[4] = new GLTriangle(_mt, cube5, texcoords, colors, indexes, 6);
	_tri[5] = new GLTriangle(_mt, cube6, texcoords, colors, indexes, 6);

	return STATUS_OK;
}

void OpenGLES100GraphicsService::deinit(){

	delete _mt;
	for( int32_t i = 0; i < squares; ++i ){
		delete _tri[i];
	}

	LOGI_OGLESS("deinit begin");

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

	LOGI_OGLESS("deinit end");
}

} /* namespace opengles_test */
