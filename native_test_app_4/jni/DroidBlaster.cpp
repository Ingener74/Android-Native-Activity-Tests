/*
 * DroidBlaster.cpp
 *
 *  Created on: 26.01.2013
 *      Author: pavel
 */

#include "DroidBlaster.h"
#include "Log.h"

namespace smallarsdk {

DroidBlaster::DroidBlaster( Context& context, android_app* application ):
	_application(application),
	_timeService(context.timeService),
	_graphicsService(context.graphicsService),
	_initialized(false),
	_posX(0), _posY(0), _size(24), _speed(100.f){
	Log::info("Creating DroidBlaster");
}

DroidBlaster::~DroidBlaster(){
	Log::info("Desctructing DroidBlaster");
}

status DroidBlaster::onActivate(){
	Log::info("Activating DroidBlaster");

	_timeService->reset();

//	ANativeWindow* window = _application->window;
//	if(ANativeWindow_setBuffersGeometry(window, 0, 0,
//			WINDOW_FORMAT_RGBX_8888) < 0){
//		return STATUS_KO;
//	}
//	if(ANativeWindow_lock(window, &_windowBuffer, NULL) >= 0){
//		ANativeWindow_unlockAndPost(window);
//	}else{
//		return STATUS_KO;
//	}
//	if(!_initialized){
//		_posX = _windowBuffer.width  / 2;
//		_posY = _windowBuffer.height / 2;
//		_initialized = true;
//	}

	if(_graphicsService->start() != STATUS_OK){
		return STATUS_KO;
	}

	return STATUS_OK;
}

void DroidBlaster::onDeactivate(){
	Log::info("Deactivating DroidBlaster");
	_graphicsService->stop();
}

status DroidBlaster::onStep(){
	Log::info("Starting step");

//	usleep(300000);

	_timeService->update();

//	_posX = int(_posX + _speed*_timeService->elapsed()) % int(_windowBuffer.width);
//
//	ANativeWindow* window = _application->window;
//	if(ANativeWindow_lock(window, &_windowBuffer, NULL) >= 0){
//		clear();
//		drawCursor(_size, _posX, _posY);
//		ANativeWindow_unlockAndPost(window);
//		return STATUS_OK;
//	}else{
//		return STATUS_KO;
//	}

	_graphicsService->update();

	Log::info("Stepping done");
	return STATUS_OK;
}

void DroidBlaster::onStart(){
	Log::info("onStart");
}

void DroidBlaster::clear(){
	memset(_windowBuffer.bits, 0, _windowBuffer.stride *
			_windowBuffer.height * sizeof(uint32_t));
}

void DroidBlaster::drawCursor( int size, int x, int y ){
	const int halfSize = size / 2;

	const int upLeftX = x - halfSize;
	const int upLeftY = y - halfSize;

	const int downRightX = x + halfSize;
	const int downRightY = y + halfSize;

	uint32_t* line = reinterpret_cast<uint32_t*>(_windowBuffer.bits) +
			(_windowBuffer.stride * upLeftY );

	for( int i = upLeftY; i <= downRightY; ++i ){
		for( int j = upLeftX; j <= downRightX; ++j ){
			line[j] = 255;
		}
		line = line + _windowBuffer.stride;
	}
}

} /* namespace handtracker */









