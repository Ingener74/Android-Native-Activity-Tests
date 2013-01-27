/*
 * TimeService.cpp
 *
 *  Created on: 27.01.2013
 *      Author: pavel
 */

#include "TimeService.h"
#include "Log.h"

namespace smallarsdk {

TimeService::TimeService(): _elapsed(0), _lastTime(0) {
}

TimeService::~TimeService() {
}

void TimeService::reset(){
	Log::info("Resetting time service");
	_elapsed = 0;
	_lastTime = now();
}

void TimeService::update(){
	double currentTime = now();
	_elapsed = currentTime - _lastTime;
	_lastTime = currentTime;
}

double TimeService::now(){
	timespec timeVal;
	clock_gettime(CLOCK_MONOTONIC, &timeVal);
	return timeVal.tv_sec + (timeVal.tv_nsec * 1.0e-9);
}

float TimeService::elapsed(){
	return _elapsed;
}

} /* namespace smallarsdk */
