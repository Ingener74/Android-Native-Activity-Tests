/*
 * OpenGLES10EventHandler.cpp
 *
 *  Created on: 10.03.2013
 *      Author: pavel
 */

#include "OpenGLES10EventHandler.h"

OpenGLES10EventHandler::OpenGLES10EventHandler( android_app* app, IGraphicsService* gs ):
	IEventEngine(app),_gs(gs) {
	LOGW_OGLES10EH("constructor");
}

OpenGLES10EventHandler::~OpenGLES10EventHandler() {
	LOGW_OGLES10EH("desttuctor");
}

void OpenGLES10EventHandler::run(){

	LOGI_OGLES10EH("run");

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

void OpenGLES10EventHandler::onInitWindow(){
	LOGI_OGLES10EH("on init window");

	if(_gs){
		_gs->init(_application);
		_onFocus = true;
	}
}

void OpenGLES10EventHandler::onTermWindow(){
	LOGI_OGLES10EH("on term window");
	if(_gs)
		_gs->deinit();
}

void OpenGLES10EventHandler::onGainedFocus(){
	LOGI_OGLES10EH("on gained focus");
	_onFocus = true;
}

void OpenGLES10EventHandler::onLostFocus(){
	LOGI_OGLES10EH("on lost focus");
	_onFocus = false;
}
