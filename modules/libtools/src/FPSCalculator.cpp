/*
 * FPSCalculator.cpp
 *
 *  Created on: 09.03.2013
 *      Author: pavel
 */

#include "FPSCalculator.h"

FPSCalculator::FPSCalculator(): _start(0), _fps(0){
}

FPSCalculator::~FPSCalculator() {
}

void FPSCalculator::start(void){
	_start = clock();
}

void FPSCalculator::stop(void){
	_fps = _ms_in_sec /
			(double( double(clock()) - _start) /
					double(CLOCKS_PER_SEC / _ms_in_sec));
}

double FPSCalculator::getFPS(){
	return _fps;
}

const char* FPSCalculator::getFPS( const char* name ){
	sprintf(_fps_buffer, "fps of %s = %f", name, _fps);
	return _fps_buffer;
}
