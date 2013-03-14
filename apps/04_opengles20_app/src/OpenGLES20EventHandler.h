/*
 * OpenGLES20EventHandler.h
 *
 *  Created on: 13.03.2013
 *      Author: pavel
 */

#ifndef OPENGLES20EVENTHANDLER_H_
#define OPENGLES20EVENTHANDLER_H_

#include <IEventEngine.h>

class OpenGLES20EventHandler: public IEventEngine {
public:
	OpenGLES20EventHandler( android_app* app );
	virtual ~OpenGLES20EventHandler();

	void run();

	void onInitWindow();
	void onTermWindow();

	void onGainedFocus();
	void onLostFocus();
};

#endif /* OPENGLES20EVENTHANDLER_H_ */
