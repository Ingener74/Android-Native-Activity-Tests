/*
 * EmptyAppEventHandler.cpp
 *
 *  Created on: 10.03.2013
 *      Author: pavel
 */

#include "EmptyAppEventHandler.h"

EmptyAppEventHandler::EmptyAppEventHandler( android_app* app ):
	IEventEngine(app), _app(app) {
	LOGW_EAEH("constructor");
}

EmptyAppEventHandler::~EmptyAppEventHandler() {
	LOGW_EAEH("destructor");
}

void EmptyAppEventHandler::run(){

	int32_t outEvents = 0, num = 0;
	android_poll_source* source = NULL;

	while(1){
		while( (num = ALooper_pollAll(-1, NULL, &outEvents, (void**)&source))
				>= 0 ){
			if(source){
				source->process(_app, source);
			}else{
				LOGE_EAEH("source null");
			}

			if(_app->destroyed){
				LOGW_EAEH("application destroyed");
				return;
			}
		}
	}
}

void EmptyAppEventHandler::onInitWindow(){
	LOGI_EAEH("onInitWindow");
}

void EmptyAppEventHandler::onTermWindow(){
	LOGI_EAEH("onTermWindow");
}

void EmptyAppEventHandler::onGainedFocus(){
	LOGI_EAEH("onGainedFocus");
}

void EmptyAppEventHandler::onLostFocus(){
	LOGI_EAEH("onLostFocus");
}
