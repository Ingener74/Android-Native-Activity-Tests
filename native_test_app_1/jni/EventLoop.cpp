/*
 * EventLoop.cpp
 *
 *  Created on: 25.01.2013
 *      Author: pavel
 */

#include "EventLoop.h"
#include "Log.h"

namespace smallarsdk {

EventLoop::EventLoop( android_app* application ): _application(application){}

void EventLoop::run(){
	int32_t result;
	int32_t events;

	android_poll_source* source;

	app_dummy();

	Log::info("Starting event loop");

	while( true ){
		while( (result = ALooper_pollAll(-1, NULL, &events, (void**)&source)) >= 0 ){
			if(source != NULL){
				Log::info("Processing an event");
				source->process(_application, source);
			}

		}
	}
}

}
