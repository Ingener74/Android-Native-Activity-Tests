/*
 * EventLoop.h
 *
 *  Created on: 25.01.2013
 *      Author: pavel
 */

#ifndef EVENTLOOP_H_
#define EVENTLOOP_H_

#include "ActivityHandler.h"
#include "Types.hpp"

#include <android_native_app_glue.h>

namespace smallarsdk {

class EventLoop {

public:
	EventLoop( android_app* application );
	void run( ActivityHandler& activityHandler );

protected:
	void activate();
	void deactivate();

	void processActivityEvent( int32_t command );

private:
	static void activityCallback(android_app* application, int32_t command);

private:
	android_app*      _application;
	ActivityHandler*  _activityHandler;
	bool              _enabled;
	bool              _quit;
};

}
#endif /* EVENTLOOP_H_ */
