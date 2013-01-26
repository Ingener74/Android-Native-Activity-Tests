/*
 * main.cpp
 *
 *  Created on: 25.01.2013
 *      Author: pavel
 */

#include "EventLoop.h"
#include "DroidBlaster.h"

void android_main( android_app* _application ){

	smallarsdk::EventLoop eventLoop(_application);
	smallarsdk::DroidBlaster droidBlaster;
	eventLoop.run(droidBlaster);
}
