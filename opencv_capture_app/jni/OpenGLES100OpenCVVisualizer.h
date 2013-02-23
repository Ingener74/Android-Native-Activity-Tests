/*
 * OpenGLES100OpenCVVisualizer.h
 *
 *  Created on: Feb 21, 2013
 *      Author: ingener
 */

#ifndef OPENGLES100OPENCVVISUALIZER_H_
#define OPENGLES100OPENCVVISUALIZER_H_

#include <GLES/gl.h>
#include <GLES/glext.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>

#include <IGraphicsService.h>
#include <GLTriangle.h>
#include <RGBTexture.h>

#include <tools.h>

using namespace opengles_test;

#define LOGI_OGLES(...){ LOGI("OpenGLES100_OpenCVVisualizer", __VA_ARGS__); }

class OpenGLES100_OpenCVVisualizer: public IGraphicsService {
public:
	OpenGLES100_OpenCVVisualizer();
	virtual ~OpenGLES100_OpenCVVisualizer();

	IGraphicsService::STATUS init( android_app* application );
	void deinit();

	void draw();

private:
	android_app* _app;

	EGLDisplay  _display;
	EGLContext  _context;
	EGLSurface  _surface;

	EGLint      _width;
	EGLint      _height;

	IObject*    _scr;
	RGBTexture* _mt;

	static int32_t _tex_size;
	static int32_t _tex_im_h;
	static int32_t _tex_im_w;
	static GLfloat _scr_vertex[];
	static GLfloat _scr_tex_coords[];
	static GLfloat _scr_colors[];
	static GLushort _scr_indexes[];
};



#endif /* OPENGLES100OPENCVVISUALIZER_H_ */
