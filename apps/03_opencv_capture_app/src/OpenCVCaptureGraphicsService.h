/*
 * OpenCVCaptureGraphicsService.h
 *
 *  Created on: 11.03.2013
 *      Author: pavel
 */

#ifndef OPENCVCAPTUREGRAPHICSSERVICE_H_
#define OPENCVCAPTUREGRAPHICSSERVICE_H_

#include <GLES/gl.h>
#include <EGL/egl.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <IGraphicsService.h>
#include <RGBTexture.h>
#include <FastEGLTexture.h>
#include <GLTriangle.h>
#include <tools.h>

#define LOGI_OCVCGS(...){ LOGI("OpenCVCaptureEventHandler", __VA_ARGS__); }
#define LOGE_OCVCGS(...){ LOGE("OpenCVCaptureEventHandler", __VA_ARGS__); }
#define LOGW_OCVCGS(...){ LOGW("OpenCVCaptureEventHandler", __VA_ARGS__); }

class OpenCVCaptureGraphicsService: public IGraphicsService {
public:
	typedef IGraphicsService::STATUS STATUS;

	OpenCVCaptureGraphicsService();
	virtual ~OpenCVCaptureGraphicsService();

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

	const static bool _fast = true;
	RGBTexture*       _mt;
	FastEGLTexture*   _ft;

	IObject*    _screen;
	bool        _isInit;
};

#endif /* OPENCVCAPTUREGRAPHICSSERVICE_H_ */
