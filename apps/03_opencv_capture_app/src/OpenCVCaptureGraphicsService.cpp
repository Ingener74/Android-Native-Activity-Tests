/*
 * OpenCVCaptureGraphicsService.cpp
 *
 *  Created on: 11.03.2013
 *      Author: pavel
 */

#include "OpenCVCaptureGraphicsService.h"

const static GLfloat side = 100.f;
GLfloat vertex[] = {
		0.f,   0.f, 0.f,
		side,  0.f, 0.f,
		side, side, 0.f,
		0.f,  side, 0.f
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
		1.f, 1.f, 1.f, 1.f
};

GLushort indexes[] = {
		0, 2, 1,
		2, 0, 3
};

const uint16_t texSize = 1024;

OpenCVCaptureGraphicsService::OpenCVCaptureGraphicsService() :
		_display(EGL_NO_DISPLAY), _context(EGL_NO_CONTEXT), _surface(
				EGL_NO_SURFACE), _width(0), _height(0), _mt(NULL), _ft(NULL),
				_screen(NULL), _isInit(false) {
}

OpenCVCaptureGraphicsService::~OpenCVCaptureGraphicsService() {
}

OpenCVCaptureGraphicsService::STATUS OpenCVCaptureGraphicsService::init( android_app* app ){
	_application = app;

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
		LOGE_OCVCGS("Unable to eglMakeCurrent");
		return STATUS_ERROR;
	}
	eglQuerySurface(_display, _surface, EGL_WIDTH, &_width);
	eglQuerySurface(_display, _surface, EGL_HEIGHT, &_height);

	const double dim = 200.0;
	const double aspect = _height / double(_width);
	glViewport(0, 0, _width, _height);
	LOGE_OCVCGS("h = %d, w = %d", _height, _width);

//	glOrthof(-dim, dim, -aspect*dim, aspect*dim, - dim * 100.f, dim * 100.f);
	glOrthof(0, dim, dim, 0, - dim * 100.f, dim * 100.f);
	vertex[3] = dim;
	vertex[6] = dim;

	vertex[7] = dim;
	vertex[10] = dim;

	Mat tex_im(texSize, texSize, CV_8UC3, Scalar(0, 255, 255));
	if(_fast){

		EGLDispatcher::init();
		_ft = new FastEGLTexture(tex_im.data, tex_im.rows, tex_im.cols,
				FastEGLTexture::IMAGE_FORMAT_RGB888, _application, _display,
				FastEGLTexture::FEGL_TEXTURE_FORMAT_RGBA8888);
		_screen = new GLTriangle(_ft, vertex, texcoords, colors, indexes, 6);
	}
	else{
		_mt = new RGBTexture(tex_im);
		_screen = new GLTriangle(_mt, vertex, texcoords, colors, indexes, 6);
	}

	glEnable(GL_DEPTH_TEST);



	_isInit = true;

	return STATUS_OK;
}

void OpenCVCaptureGraphicsService::deinit(){
	LOGI_OCVCGS("deinit begin");

	if(_mt) delete _mt;
	if(_ft) delete _ft;
	if(_screen) delete _screen;

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

	LOGI_OCVCGS("deinit end");
}

void OpenCVCaptureGraphicsService::draw(){

	glClearColor(0.f, 0.3f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);

	if(_fast){
		if(_ft)
			_ft->bind();
	}else{
		if(_mt)
			_mt->bind();
	}

	if(_screen)
		_screen->draw();

//	glRotatef(0.3f, 1.f, 0.f, 0.f);
//	glRotatef(0.13f, 0.f, 1.f, 0.f);

	glDisable(GL_TEXTURE_2D);

	glFinish();
	eglSwapBuffers(_display, _surface);
}

void OpenCVCaptureGraphicsService::setImage( const Mat& image ){

	if(_fast && _ft){
		_ft->updatePart(image.data, image.rows, image.cols,
				FastEGLTexture::IMAGE_FORMAT_RGB888);
	}else{
		if(_mt)
			_mt->updatePart(image);
	}

	texcoords[2] = image.cols / GLfloat(texSize);
	texcoords[4] = image.cols / GLfloat(texSize);

	texcoords[5] = image.rows / GLfloat(texSize);
	texcoords[7] = image.rows / GLfloat(texSize);
}
