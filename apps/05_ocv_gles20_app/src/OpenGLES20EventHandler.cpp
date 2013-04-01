/*
 * OpenGLES20EventHandler.cpp
 *
 *  Created on: 13.03.2013
 *      Author: pavel
 */

#include "OpenGLES20EventHandler.h"

OpenGLES20EventHandler::OpenGLES20EventHandler( android_app* app,
		IGraphicsService* gs, IProcessor* ps ):
	IEventEngine(app), _isAnimate(false), _gs(gs), _ps(ps){
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

		if( _isAnimate && _gs && _gs->isInit() && _ps && !_ps->isError() ){
			_ps->process();
			_gs->draw();
		}
//		if(_isAnimate && _gs && _gs->isInit() ){
//			if(_cs && !_cs->isError() ){
//				_cs->grab();
//
//				_gs->setImage(_cs->getImage());
//			}
//			_gs->draw();
//		}
	}
}

void OpenGLES20EventHandler::onInitWindow(){
	if(_gs){
		if( _gs->init(_application) == IGraphicsService::STATUS_OK ){
			_isAnimate = true;
		}else{
			LOGE_OGLES20EH("graphics service status error");
		}
	}
}

void OpenGLES20EventHandler::onTermWindow(){
	_isAnimate = false;
	if(_gs){
		_gs->deinit();
	}
	for( uint16_t i = 0; i < _forStop.size(); ++i ){
		_forStop[i]->stop();
	}
}

void OpenGLES20EventHandler::onGainedFocus(){
	_isAnimate = true;
}

void OpenGLES20EventHandler::onLostFocus(){
	_isAnimate = false;
}

void OpenGLES20EventHandler::addService( IService* s ){
	_forStop.push_back(s);
}
