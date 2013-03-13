/*
 * OpenCVCaptureEventHandler.h
 *
 *  Created on: 11.03.2013
 *      Author: pavel
 */

#ifndef OPENCVCAPTUREEVENTHANDLER_H_
#define OPENCVCAPTUREEVENTHANDLER_H_

#include <IGraphicsService.h>
#include <IEventEngine.h>
#include <IProcessor.h>
#include <tools.h>

#define LOGI_OCVCEH(...){ LOGI("OpenCVCaptureEventHandler", __VA_ARGS__); }
#define LOGE_OCVCEH(...){ LOGE("OpenCVCaptureEventHandler", __VA_ARGS__); }
#define LOGW_OCVCEH(...){ LOGW("OpenCVCaptureEventHandler", __VA_ARGS__); }

class OpenCVCaptureEventHandler: public IEventEngine {
public:
	OpenCVCaptureEventHandler( android_app* app, IGraphicsService* gs, IProcessor* ps );
	virtual ~OpenCVCaptureEventHandler();

	void run();

	void onInitWindow();
	void onTermWindow();

	void onGainedFocus();
	void onLostFocus();

private:
	IGraphicsService* _gs;
	IProcessor*       _ps;

	bool _onFocus;
};

#endif /* OPENCVCAPTUREEVENTHANDLER_H_ */
