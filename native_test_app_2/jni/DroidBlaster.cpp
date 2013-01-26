/*
 * DroidBlaster.cpp
 *
 *  Created on: 26.01.2013
 *      Author: pavel
 */

#include "DroidBlaster.h"
#include "Log.h"

namespace smallarsdk {

DroidBlaster::DroidBlaster(){
	Log::info("Creating DroidBlaster");
}

DroidBlaster::~DroidBlaster(){
	Log::info("Desctructing DroidBlaster");
}

status DroidBlaster::onActivate(){
	Log::info("Activating DroidBlaster");
	return STATUS_OK;
}

void DroidBlaster::onDeactivate(){
	Log::info("Deactivating DroidBlaster");
}

status DroidBlaster::onStep(){
	Log::info("Starting step");

	usleep(300000);

	Log::info("Stepping done");
	return STATUS_OK;
}

void DroidBlaster::onStart(){
	Log::info("onStart");
}

} /* namespace handtracker */
