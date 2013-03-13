/*
 * IEventEngine.h
 *
 *  Created on: 17.02.2013
 *      Author: pavel
 */

#ifndef IEVENTENGINE_H_
#define IEVENTENGINE_H_

#include "tools.h"
#include <android/log.h>
#include <android/looper.h>
#include <android_native_app_glue.h>

#define LOGI_IEE(...){ LOGI("IEventEngine", __VA_ARGS__)}

class IEventEngine {
public:
	IEventEngine( struct android_app* application );
	virtual ~IEventEngine();

	virtual void run() = 0;

	virtual void onInputChanged(){}
	virtual void onInitWindow(){}
	virtual void onTermWindow(){}
	virtual void onWindowResized(){}
	virtual void onWindowRedrawNeeded(){}
	virtual void onContentRectChanged(){}
	virtual void onGainedFocus(){}
	virtual void onLostFocus(){}
	virtual void onConfigChanged(){}
	virtual void onLowMemory(){}
	virtual void onStart(){}
	virtual void onResume(){}
	virtual void onSaveState(){}
	virtual void onPause(){}
	virtual void onStop(){}
	virtual void onDestroy(){}

protected:
	android_app* _application;

	static void applicationCommand( struct android_app* application, int32_t command );
	static int32_t inputEvent( struct android_app* application, AInputEvent* event );
};

#endif /* IEVENTENGINE_H_ */
