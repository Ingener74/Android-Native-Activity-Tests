/*
 * OpenGLES10EventHandler.h
 *
 *  Created on: 10.03.2013
 *      Author: pavel
 */

#ifndef OPENGLES10EVENTHANDLER_H_
#define OPENGLES10EVENTHANDLER_H_

#include <IEventEngine.h>
#include <IGraphicsService.h>

#define LOGI_OGLES10EH(...){ LOGI("OpenGLES10EventHandler", __VA_ARGS__); }
#define LOGE_OGLES10EH(...){ LOGE("OpenGLES10EventHandler", __VA_ARGS__); }
#define LOGW_OGLES10EH(...){ LOGW("OpenGLES10EventHandler", __VA_ARGS__); }

class OpenGLES10EventHandler: public IEventEngine {
public:
	OpenGLES10EventHandler( android_app* app, IGraphicsService* gs = NULL );
	virtual ~OpenGLES10EventHandler();

	void run();

	void onInitWindow();
	void onTermWindow();

	void onGainedFocus();
	void onLostFocus();

private:
	IGraphicsService* _gs;

	bool _onFocus;
};

#endif /* OPENGLES10EVENTHANDLER_H_ */
