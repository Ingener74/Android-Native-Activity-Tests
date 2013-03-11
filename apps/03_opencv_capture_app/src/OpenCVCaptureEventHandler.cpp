/*
 * OpenCVCaptureEventHandler.cpp
 *
 *  Created on: 11.03.2013
 *      Author: pavel
 */

#include "OpenCVCaptureEventHandler.h"

OpenCVCaptureEventHandler::OpenCVCaptureEventHandler(android_app* app,
		IGraphicsService* gs,
		IProcessor* ps ) :
		IEventEngine(app), _gs(gs), _ps(ps), _onFocus(false) {
}

OpenCVCaptureEventHandler::~OpenCVCaptureEventHandler() {
}

void OpenCVCaptureEventHandler::run(){

	LOGI_OCVCEH("run");

	while(1){

		int32_t outEvents = 0;
		android_poll_source* source;
		while( ALooper_pollAll( _onFocus ? 0 : -1, NULL,  &outEvents, (void**)&source) > 0 ){
			if(source)
				source->process(_application, source);

			if(_application->destroyed)
				return;
		}

		if(_gs && _gs->isInit())
			_gs->draw();
	}
}

void OpenCVCaptureEventHandler::onInitWindow() {
	LOGI_OCVCEH("on init window");

	if (_gs) {
		_gs->init(_application);
		_onFocus = true;
	}
}

void OpenCVCaptureEventHandler::onTermWindow() {
	LOGI_OCVCEH("on term window");
	if (_gs)
		_gs->deinit();
}

void OpenCVCaptureEventHandler::onGainedFocus() {
	LOGI_OCVCEH("on gained focus");
	_onFocus = true;
}

void OpenCVCaptureEventHandler::onLostFocus() {
	LOGI_OCVCEH("on lost focus");
	_onFocus = false;
}
