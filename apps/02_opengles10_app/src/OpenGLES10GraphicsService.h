/*
 * OpenGLES10GraphicsService.h
 *
 *  Created on: 10.03.2013
 *      Author: pavel
 */

#ifndef OPENGLES10GRAPHICSSERVICE_H_
#define OPENGLES10GRAPHICSSERVICE_H_

#include <GLES/gl.h>
#include <EGL/egl.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <IGraphicsService.h>
#include <RGBTexture.h>
#include <GLTriangle.h>
#include <tools.h>

#define LOGI_OGLES10GS(...){ LOGI("OpenGLES10GraphicsService", __VA_ARGS__); }
#define LOGE_OGLES10GS(...){ LOGE("OpenGLES10GraphicsService", __VA_ARGS__); }
#define LOGW_OGLES10GS(...){ LOGW("OpenGLES10GraphicsService", __VA_ARGS__); }

using namespace cv;

class OpenGLES10GraphicsService: public IGraphicsService{
public:
	typedef IGraphicsService::STATUS STATUS;

	OpenGLES10GraphicsService();
	virtual ~OpenGLES10GraphicsService();

	STATUS init( android_app* app );

	bool isInit(){
		return _isInit;
	}

	void deinit();

	void draw();

	void setImage( const Mat& image );

private:
	EGLDisplay  _display;
	EGLContext  _context;
	EGLSurface  _surface;

	EGLint      _width;
	EGLint      _height;

	static const int32_t squares = 6;
	ITexture*   _mt;
	IObject*    _tri[squares];
	bool _isInit;
};

#endif /* OPENGLES10GRAPHICSSERVICE_H_ */
