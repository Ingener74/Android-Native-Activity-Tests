/*
 * OpenCVEvent.cpp
 *
 *  Created on: Feb 21, 2013
 *      Author: ingener
 */

#include "OpenCVEvent.h"

OpenCVEvent::OpenCVEvent( android_app* application,
		IGraphicsService* graphicsService, ICaptureService* captureService ):
		IEventEngine(application), _app(application), _gs(graphicsService),
		_cs(captureService), _animate(false) {
	LOGI_OCVE("OpenCVEvent constr");
}

OpenCVEvent::~OpenCVEvent() {
	LOGI_OCVE("OpenCVEvent destcr");
}

void OpenCVEvent::run(){
	LOGI_OCVE("OpenCVEvent run begin");
	app_dummy();

	int32_t num = 0;
	int32_t event = 0;
	android_poll_source* source;

	while( true ){
		while( (num = ALooper_pollAll( (_animate ? 0 : -1 ), 0, &event,
				(void**)&source)) >= 0 ){

			if(source)
				source->process(_application, source);

			if(_application->destroyed){
				return;
			}

		}

		if(_cs){
			_cs->grab();
			if(_gs){
				_gs->setImage(_cs->getImage());
			}
		}

		if(_animate && _gs ){
			LOGI_OCVE("OpenCVEvent animate true, gs->draw");
			_gs->draw();
		}
	}
	LOGI_OCVE("OpenCVEvent run end");
}

void OpenCVEvent::onInitWindow(){
	LOGI_OCVE("OpenCVEvent onInitWindow begin");
	if(_gs && _app){
		_gs->init(_app);
		_animate = true;
	}
	LOGI_OCVE("OpenCVEvent onInitWindow end");
}

void OpenCVEvent::onTermWindow(){
	LOGI_OCVE("OpenCVEvent onTermWindow begin");
	_animate = false;
	if(_gs){
		_gs->deinit();
	}
	LOGI_OCVE("OpenCVEvent onTermWindow end");
}

