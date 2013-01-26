/*
 * EventLoop.h
 *
 *  Created on: 25.01.2013
 *      Author: pavel
 */

#ifndef EVENTLOOP_H_
#define EVENTLOOP_H_

#include <android_native_app_glue.h>

namespace smallarsdk {

class EventLoop {
public:
	EventLoop( android_app* application );

	void run();
private:
	android_app* _application;
};

}
#endif /* EVENTLOOP_H_ */
