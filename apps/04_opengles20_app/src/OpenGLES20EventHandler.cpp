/*
 * OpenGLES20EventHandler.cpp
 *
 *  Created on: 13.03.2013
 *      Author: pavel
 */

#include "OpenGLES20EventHandler.h"

OpenGLES20EventHandler::OpenGLES20EventHandler( android_app* app, IGraphicsService* gs ):
	IEventEngine(app), _isAnimate(false), _gs(gs){
}

OpenGLES20EventHandler::~OpenGLES20EventHandler() {
}

void OpenGLES20EventHandler::run(){
	LOGI_OGLES20EH("run begin");

	int32_t event = 0;

	android_poll_source* source;
	while(1){
		while( ALooper_pollAll(_isAnimate ? 0 : -1, NULL, &event, (void**)&source) > 0 ){
			if(source)
				source->process(_application, source);
			if(_application->destroyed){
				return;
			}
		}

		if(_isAnimate && _gs && _gs->isInit() ){
			_gs->draw();
		}
	}
}

void OpenGLES20EventHandler::onInitWindow(){
	if(_gs){
		_gs->init(_application);
		_isAnimate = true;
	}
}

void OpenGLES20EventHandler::onTermWindow(){
	_isAnimate = false;
	if(_gs){
		_gs->deinit();
	}
}

void OpenGLES20EventHandler::onGainedFocus(){
}

void OpenGLES20EventHandler::onLostFocus(){
}
