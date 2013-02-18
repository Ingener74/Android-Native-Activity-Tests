/*
 * NativeWindowGraphicsService.h
 *
 *  Created on: 18.02.2013
 *      Author: pavel
 */

#ifndef NATIVEWINDOWGRAPHICSSERVICE_H_
#define NATIVEWINDOWGRAPHICSSERVICE_H_

#include <android/window.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "IGraphicsService.h"
#include "ICaptureService.h"
#include "tools.h"

using namespace cv;
using namespace opengles_test;

#define LOGI_NWGS(...){ LOGI("NativeWindowGraphicsService", __VA_ARGS__); }

class NativeWindowGraphicsService: public IGraphicsService {
public:
	NativeWindowGraphicsService( ICaptureService* captureService );
	virtual ~NativeWindowGraphicsService();

	virtual IGraphicsService::STATUS init( android_app* application );
	virtual void deinit();

	virtual void draw();

protected:
	ICaptureService*     _cs;

	ANativeWindow_Buffer _windowBuffer;
	Mat                  _outImage;

//	VideoCapture         vc;
};

#endif /* NATIVEWINDOWGRAPHICSSERVICE_H_ */
