/*
 * OpenCVEvent.h
 *
 *  Created on: Feb 21, 2013
 *      Author: ingener
 */

#ifndef OPENCVEVENT_H_
#define OPENCVEVENT_H_

#include <IEventEngine.h>
#include <IGraphicsService.h>
#include <ICaptureService.h>

#include <tools.h>

using namespace nae;
using namespace opengles_test;

#define LOGI_OCVE(...){ LOGI("OpenCVEvent", __VA_ARGS__); }

class OpenCVEvent: public IEventEngine {
public:
	OpenCVEvent( android_app* application, IGraphicsService* graphicsService,
			ICaptureService* captureService );
	virtual ~OpenCVEvent();

	void run();

	void onInitWindow();
	void onTermWindow();

private:
	android_app*      _app;
	IGraphicsService* _gs;
	ICaptureService*  _cs;
	bool              _animate;
};

#endif /* OPENCVEVENT_H_ */
