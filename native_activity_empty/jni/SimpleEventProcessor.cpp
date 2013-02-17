/*
 * SimpleEventProcessor.cpp
 *
 *  Created on: 17.02.2013
 *      Author: pavel
 */

#include "SimpleEventProcessor.h"

namespace nae {

SimpleEventProcessor::SimpleEventProcessor( android_app* application ):
		IEventEngine(application){
}

SimpleEventProcessor::~SimpleEventProcessor() {
}

void SimpleEventProcessor::run(){

	LOGI_SEP("run begin");

	int32_t num = 0;

	int32_t fd = 0, event = 0;

	while( true ){
		while( (num = ALooper_pollAll(-1, &fd, &event, 0)) >= 0 ){
			LOGI_SEP("num = %d", num);
			LOGI_SEP("fd = %d", fd);
			LOGI_SEP("events = %d", event);

			if(_application->destroyed){
				return;
				LOGI_SEP("application destroyed");
			}
		}
	}

	LOGI_SEP("run end");
}

void SimpleEventProcessor::onInitWindow(){

}

void SimpleEventProcessor::onTermWindow(){
}

} /* namespace nae */
