/*
 * main.cpp
 *
 *  Created on: 25.01.2013
 *      Author: pavel
 */

#include "EventLoop.h"
#include "DroidBlaster.h"
#include "TimeService.h"
#include "Context.h"
#include "Log.h"

void android_main( android_app* application ){

	smallarsdk::TimeService timeService;
	smallarsdk::GraphicsService graphicsService(application, &timeService);
	smallarsdk::Context context = {
			&graphicsService,
			&timeService
	};

	smallarsdk::EventLoop eventLoop(application);

	smallarsdk::DroidBlaster droidBlaster(context, application);

	eventLoop.run(droidBlaster);
}
