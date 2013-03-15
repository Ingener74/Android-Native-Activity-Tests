/*
 * OpenGLES20EventHandler.h
 *
 *  Created on: 13.03.2013
 *      Author: pavel
 */

#ifndef OPENGLES20EVENTHANDLER_H_
#define OPENGLES20EVENTHANDLER_H_

#include <IEventEngine.h>
#include <IGraphicsService.h>
#include <tools.h>

#define LOGI_OGLES20EH(...){ LOGI("OpenGLES20EventHandler", __VA_ARGS__); }
#define LOGE_OGLES20EH(...){ LOGE("OpenGLES20EventHandler", __VA_ARGS__); }
#define LOGW_OGLES20EH(...){ LOGW("OpenGLES20EventHandler", __VA_ARGS__); }


class OpenGLES20EventHandler: public IEventEngine {
public:
	OpenGLES20EventHandler( android_app* app, IGraphicsService* gs );
	virtual ~OpenGLES20EventHandler();

	void run();

	void onInitWindow();
	void onTermWindow();

	void onGainedFocus();
	void onLostFocus();

private:
	bool               _isAnimate;
	IGraphicsService*  _gs;
};

#endif /* OPENGLES20EVENTHANDLER_H_ */
