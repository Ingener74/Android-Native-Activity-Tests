/*
 * EventLoop.cpp
 *
 *  Created on: 25.01.2013
 *      Author: pavel
 */

#include "EventLoop.h"
#include "Log.h"

namespace smallarsdk {

EventLoop::EventLoop( android_app* application ):
		_application(application),
		_activityHandler(NULL),
		_enabled(false),
		_quit(false){
	_application->onAppCmd = activityCallback;
	_application->userData = this;
}

void EventLoop::run( ActivityHandler& activityHandler ){
	int32_t result;
	int32_t events;

	android_poll_source* source;

	app_dummy();

	Log::info("Starting event loop");

	while( true ){
		while( (result = ALooper_pollAll(_enabled ? 0 : -1, NULL, &events, (void**)&source)) >= 0 ){
			if(source != NULL){
				Log::info("Processing an event");
				source->process(_application, source);
			}
			if(_application->destroyRequested){
				Log::info("Exiting event loop");
				return;
			}
		}
		if((_enabled) && (!_quit)){
			if(_activityHandler->onStep() != STATUS_OK){
				_quit = true;
				ANativeActivity_finish(_application->activity);
			}
		}
	}
}

void EventLoop::processActivityEvent( int32_t command ){
	switch(command){
	case APP_CMD_CONFIG_CHANGED:{
		_activityHandler->onConfigurationChanged();
		break;
	}
	case APP_CMD_INIT_WINDOW:{
		_activityHandler->onCreateWindow();
		break;
	}
	case APP_CMD_DESTROY:{
		_activityHandler->onDestroy();
		break;
	}
	case APP_CMD_GAINED_FOCUS:{
		activate();
		_activityHandler->onGainFocus();
		break;
	}
	case APP_CMD_LOST_FOCUS:{
		_activityHandler->onLostFocus();
		deactivate();
		break;
	}
	case APP_CMD_LOW_MEMORY:{
		_activityHandler->onLowMemory();
		break;
	}
	case APP_CMD_PAUSE:{
		_activityHandler->onPause();
		deactivate();
		break;
	}
	case APP_CMD_RESUME:{
		_activityHandler->onResume();
		break;
	}
	case APP_CMD_SAVE_STATE:{
		_activityHandler->onSaveState(
				&_application->savedState,
				(int32_t*)&_application->savedStateSize);
		break;
	}
	case APP_CMD_START:{
		_activityHandler->onStart();
		break;
	}
	case APP_CMD_STOP:{
		_activityHandler->onStop();
		break;
	}
	case APP_CMD_TERM_WINDOW:{
		_activityHandler->onDestroyWindow();
		deactivate();
		break;
	}
	default:
		break;
	}
}

void EventLoop::activityCallback( android_app* application, int32_t command ){
	EventLoop& eventLoop = *(EventLoop*)application->userData;
	eventLoop.processActivityEvent(command);
}

void EventLoop::activate(){
	if( !_enabled && _application->window != NULL ){
		_quit = false;
		_enabled = true;

		if(_activityHandler->onActivate() != STATUS_OK){
			_quit = true;
			ANativeActivity_finish(_application->activity);
		}
	}
}

void EventLoop::deactivate(){
	if(_enabled){
		_activityHandler->onDeactivate();
		_enabled = false;
	}
}

}









