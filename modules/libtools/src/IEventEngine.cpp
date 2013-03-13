/*
 * IEventEngine.cpp
 *
 *  Created on: 17.02.2013
 *      Author: pavel
 */

#include "IEventEngine.h"

IEventEngine::IEventEngine( struct android_app* application ):
		_application(application){

	LOGI_IEE("IEventEngine constructor begin");

	app_dummy();

	_application->userData = (void*)this;
	_application->onAppCmd = IEventEngine::applicationCommand;
	_application->onInputEvent = IEventEngine::inputEvent;

	LOGI_IEE("IEventEngine constructor begin");
}

IEventEngine::~IEventEngine(){
	LOGI_IEE("IEventEngine destructor");
}

void IEventEngine::applicationCommand( struct android_app* application,
		int32_t command ){
	LOGI_IEE("application Command begin");

	IEventEngine* engine = static_cast<IEventEngine*>(application->userData);

	switch(command){
	case APP_CMD_INPUT_CHANGED:{
		engine->onInputChanged();
		break;
	}
	case APP_CMD_INIT_WINDOW:{
		engine->onInitWindow();
		break;
	}
	case APP_CMD_TERM_WINDOW:{
		engine->onTermWindow();
			break;
		}
	case APP_CMD_WINDOW_RESIZED:{
		engine->onWindowResized();
		break;
	}
	case APP_CMD_WINDOW_REDRAW_NEEDED:{
		engine->onWindowRedrawNeeded();
		break;
	}
	case APP_CMD_CONTENT_RECT_CHANGED:{
		engine->onContentRectChanged();
		break;
	}
	case APP_CMD_GAINED_FOCUS:{
		engine->onGainedFocus();
		break;
	}
	case APP_CMD_LOST_FOCUS:{
		engine->onLostFocus();
		break;
	}
	case APP_CMD_CONFIG_CHANGED:{
		engine->onConfigChanged();
		break;
	}
	case APP_CMD_LOW_MEMORY:{
		engine->onLowMemory();
		break;
	}
	case APP_CMD_START:{
		engine->onStart();
		break;
	}
	case APP_CMD_RESUME:{
		engine->onResume();
		break;
	}
	case APP_CMD_SAVE_STATE:{
		engine->onSaveState();
		break;
	}
	case APP_CMD_PAUSE:{
		engine->onPause();
		break;
	}
	case APP_CMD_STOP:{
		engine->onStop();
		break;
	}
	case APP_CMD_DESTROY:{
		engine->onDestroy();
		break;
	}
	}
	LOGI_IEE("application Command end");
}

int32_t IEventEngine::inputEvent( struct android_app* application,
		AInputEvent* event ){
	return 0;
}
