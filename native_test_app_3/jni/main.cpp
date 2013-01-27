/*
 * main.cpp
 *
 *  Created on: 25.01.2013
 *      Author: pavel
 */

#include "EventLoop.h"
#include "DroidBlaster.h"
#include "Log.h"

void android_main( android_app* _application ){

	smallarsdk::EventLoop eventLoop(_application);
	smallarsdk::Log::info("android main 1");
	smallarsdk::DroidBlaster droidBlaster;
	smallarsdk::Log::info("android main 2");
	eventLoop.run(droidBlaster);
	smallarsdk::Log::info("android main 3");
}
