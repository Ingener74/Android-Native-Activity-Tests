/*
 * OpenGLES100GraphicsService.h
 *
 *  Created on: Feb 18, 2013
 *      Author: ingener
 */

#ifndef OPENGLES100GRAPHICSSERVICE_H_
#define OPENGLES100GRAPHICSSERVICE_H_

#include <GLES/gl.h>
#include <EGL/egl.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "tools.h"

#include "IGraphicsService.h"

#include "RGBTexture.h"
#include "GLTriangle.h"

using namespace cv;

#define LOGI_OGLESS(...){ LOGI("OpenGLES100GraphicsService", __VA_ARGS__); }

namespace opengles_test {

class OpenGLES100GraphicsService: public IGraphicsService {
public:
	OpenGLES100GraphicsService();
	virtual ~OpenGLES100GraphicsService();

	virtual STATUS init( android_app* application );
	virtual void deinit();

	virtual void draw();

protected:
	EGLDisplay  _display;
	EGLContext  _context;
	EGLSurface  _surface;

	EGLint      _width;
	EGLint      _height;

	/*
	 * objects
	 */
	static const int32_t squares = 6;
	ITexture*   _mt;
	IObject*    _tri[squares];
};

} /* namespace opengles_test */
#endif /* OPENGLES100GRAPHICSSERVICE_H_ */
