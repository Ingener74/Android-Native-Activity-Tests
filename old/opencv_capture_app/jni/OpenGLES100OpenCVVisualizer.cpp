/*
 * OpenGLES100OpenCVVisualizer.cpp
 *
 *  Created on: Feb 21, 2013
 *      Author: ingener
 */

#include "OpenGLES100OpenCVVisualizer.h"

int32_t OpenGLES100_OpenCVVisualizer::_tex_size = 1024;
int32_t OpenGLES100_OpenCVVisualizer::_tex_im_h = 480;
int32_t OpenGLES100_OpenCVVisualizer::_tex_im_w = 640;

GLfloat OpenGLES100_OpenCVVisualizer::_scr_vertex[] = {
		0.f, 0.f, 0.f,
		100.f, 0.f, 0.f,
		100.f, 100.f, 0.f,
		0.f,   100.f, 0.f
};
GLfloat OpenGLES100_OpenCVVisualizer::_scr_tex_coords[] = {
		0.f, 0.f,
		1.f, 0.f,
		1.f, 1.f,
		0.f, 1.f
};
GLfloat OpenGLES100_OpenCVVisualizer::_scr_colors[] = {
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f
};
GLushort OpenGLES100_OpenCVVisualizer::_scr_indexes[] = {
//		1, 0, 2,
//		3, 2, 0
		0, 1, 2, 2, 3, 0
};
OpenGLES100_OpenCVVisualizer::OpenGLES100_OpenCVVisualizer():
	IGraphicsService(), _app(0), _display(EGL_NO_DISPLAY),
	_context(EGL_NO_CONTEXT), _surface(EGL_NO_SURFACE), _width(0), _height(0),
	_scr(0), _mt(0){
	LOGI_OGLES("OpenGLES100_OpenCVVisualizer constr");
}

OpenGLES100_OpenCVVisualizer::~OpenGLES100_OpenCVVisualizer() {
}

IGraphicsService::STATUS OpenGLES100_OpenCVVisualizer::init(
		android_app* application ){
	LOGI_OGLES("OpenGLES100_OpenCVVisualizer init begin");
	_app = application;

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
		LOGI_OGLES("Unable to eglMakeCurrent");
		return IGraphicsService::STATUS_ERROR;
	}
	eglQuerySurface(_display, _surface, EGL_WIDTH, &_width);
	eglQuerySurface(_display, _surface, EGL_HEIGHT, &_height);

	const double dim = 200.0;
	const double aspect = _height / double(_width);
	glViewport(0, 0, _width, _height);
	LOGI_OGLES("h = %d, w = %d", _height, _width);

	glOrthof(-dim, dim, -aspect*dim, aspect*dim, - dim * 100.f, dim * 100.f);
	LOGI_OGLES("left = %f, right = %f, bottom = %f, top = %f, zNear = %f, "
			"zFar = %f",
			-dim, dim, -aspect*dim, aspect*dim, -dim, dim);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/*
	 * creating objects
	 */

	_mt = new RGBTexture(Mat(_tex_size, _tex_size, CV_8UC3, Scalar(0, 120, 20)));
	_scr = new GLTriangle(_mt, _scr_vertex, _scr_tex_coords, _scr_colors, _scr_indexes, 6);

	LOGI_OGLES("OpenGLES100_OpenCVVisualizer init end");
	return IGraphicsService::STATUS_OK;
}

void OpenGLES100_OpenCVVisualizer::deinit(){
	LOGI_OGLES("OpenGLES100_OpenCVVisualizer deinit begin");
	delete _mt;
	delete _scr;

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
	LOGI_OGLES("OpenGLES100_OpenCVVisualizer deinit end");
}

void OpenGLES100_OpenCVVisualizer::draw(){
	LOGI_OGLES("OpenGLES100_OpenCVVisualizer draw begin");
	glClearColor(0.8f, 0.3f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);

//	static bool trans = false;
//	if( !trans ){
//		glTranslatef(0, 0, -100);
//		trans = true;
//	}

	if(_scr)
		_scr->draw();

//	glRotatef(0.3f, 1.f, 0.f, 0.f);
//	glRotatef(0.13f, 0.f, 1.f, 0.f);

	glDisable(GL_TEXTURE_2D);

	glFinish();
	eglSwapBuffers(_display, _surface);
	LOGI_OGLES("OpenGLES100_OpenCVVisualizer draw end");
}

void OpenGLES100_OpenCVVisualizer::setImage( const Mat& im ){
	im.copyTo(_visim);
}
