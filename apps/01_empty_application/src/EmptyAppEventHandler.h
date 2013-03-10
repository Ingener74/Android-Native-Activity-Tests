/*
 * EmptyAppEventHandler.h
 *
 *  Created on: 10.03.2013
 *      Author: pavel
 */

#ifndef EMPTYAPPEVENTHANDLER_H_
#define EMPTYAPPEVENTHANDLER_H_

#include <unistd.h>

#include <IEventEngine.h>
#include <tools.h>

using namespace nae;

#define LOGI_EAEH(...){ LOGI("EmptyAppEventHandler", __VA_ARGS__); }
#define LOGE_EAEH(...){ LOGE("EmptyAppEventHandler", __VA_ARGS__); }
#define LOGW_EAEH(...){ LOGW("EmptyAppEventHandler", __VA_ARGS__); }

class EmptyAppEventHandler: public IEventEngine {
public:
	EmptyAppEventHandler( android_app* app );
	virtual ~EmptyAppEventHandler();

	void run();

	void onInitWindow();
	void onTermWindow();

	void onLostFocus();
	void onGainedFocus();

private:
	android_app* _app;
};

#endif /* EMPTYAPPEVENTHANDLER_H_ */
