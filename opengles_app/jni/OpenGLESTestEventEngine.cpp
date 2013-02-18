/*
 * OpenGLESTestEventEngine.cpp
 *
 *  Created on: Feb 18, 2013
 *      Author: ingener
 */

#include "OpenGLESTestEventEngine.h"

namespace opengles_test {

OpenGLESTestEventEngine::OpenGLESTestEventEngine( android_app* application,
		IGraphicsService* graphicsService ): IEventEngine(application),
				_graphicsService(graphicsService), _animateGraphics(false) {
}

OpenGLESTestEventEngine::~OpenGLESTestEventEngine() {
}

void OpenGLESTestEventEngine::run(){

	LOGI_OGLESEE("run begin");

	int32_t num = 0;

	int32_t event = 0;
	android_poll_source* source;

	while( true ){
		while( (num = ALooper_pollAll(_animateGraphics ? 0 : -1, 0, &event,
				(void**)&source)) >= 0 ){

			if(source)
				source->process(_application, source);

			if(_application->destroyed){
				return;
				LOGI_OGLESEE("application destroyed");
			}

		}
		if(_animateGraphics && _graphicsService){
			_graphicsService->draw();
		}
	}

	LOGI_OGLESEE("run end");

}

void OpenGLESTestEventEngine::onInitWindow(){
	LOGI_OGLESEE("onInitWindow begin");
	if(_graphicsService){
		if(_graphicsService->init(_application)){
			LOGI_OGLESEE("run end");
		}
	}
	LOGI_OGLESEE("onInitWindow end");
}

void OpenGLESTestEventEngine::onTermWindow(){
	LOGI_OGLESEE("onTermWindow begin");
	if(_graphicsService){
		LOGI_OGLESEE("onTermWindow deinit");
		_graphicsService->deinit();
//		delete _graphicsService;
//		_graphicsService = 0;
	}
	LOGI_OGLESEE("onTermWindow end");
}

} /* namespace opengles_test */
