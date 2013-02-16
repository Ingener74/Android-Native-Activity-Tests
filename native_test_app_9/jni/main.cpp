/*
 * Test application for OpenGL
 */

#include <fstream>

#include <jni.h>
#include <errno.h>
#include <math.h>

#include <android/log.h>
#include <android/looper.h>
#include <android/sensor.h>
#include <android_native_app_glue.h>

#include <GLES/gl.h>
#include <EGL/egl.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "GraphicsService.h"

#include "GLTriangle.h"
#include "RGBTexture.h"

using namespace native_test_app_8;
using namespace cv;
using namespace std;

const char* caption =
		"native_test_app_9"
		;



struct saved_state{
};

class NativeTest9GS: public GraphicsService{
	saved_state* _saved_state;
public:
	NativeTest9GS( android_app* application ,saved_state* saved_state_ ):
		GraphicsService(application),
		_saved_state(saved_state_){
	}
	virtual ~NativeTest9GS(){}

	void draw(){
		if(_display != EGL_NO_DISPLAY && _saved_state != NULL ){
			glClearColor(0.f, 0.f, 0.f, 1);
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

			/*
			 * draw custom scene
			 */

			eglSwapBuffers(_display, _surface);
		}
	}
};

struct engine{
	android_app*       _app;
	ASensorManager*    _sensorMgr;
	const ASensor*     _accelerometer;
	ASensorEventQueue* _sensorEventQueue;

	NativeTest9GS*     _gs;

	saved_state        _state;
	bool               _animate;

	VideoCapture*      _cap;
};

static int32_t engineHandleInput( struct android_app* app, AInputEvent* event ){
	engine* engine_ = (engine*)app->userData;

	return 0;
}

static void engineHandleCmd( struct android_app* app, int32_t cmd){
	engine* engine_ = (engine*)app->userData;

	switch(cmd){
	case APP_CMD_SAVE_STATE:{
		engine_->_app->savedState = malloc(sizeof(saved_state));
		*((saved_state*)engine_->_app->savedState) = engine_->_state;
		engine_->_app->savedStateSize = sizeof(saved_state);
		break;
	}
	case APP_CMD_INIT_WINDOW:{
		if( engine_->_app->window != NULL ){
			LOGI("init window", "init window");
			engine_->_gs = new NativeTest9GS(engine_->_app, &engine_->_state);
			engine_->_animate = true;
			LOGI("init window", "end init window");
		}
		break;
	}
	case APP_CMD_TERM_WINDOW:{
		LOGI("native_test_app_7", "terminate window");
		delete engine_->_gs; engine_->_gs = NULL;
		engine_->_animate = false;
		break;
	}
	case APP_CMD_GAINED_FOCUS:{
		if(engine_->_accelerometer != NULL ){
			ASensorEventQueue_enableSensor(engine_->_sensorEventQueue,
					engine_->_accelerometer);
			ASensorEventQueue_setEventRate(engine_->_sensorEventQueue,
					engine_->_accelerometer, (1000 / 60)*1000);
		}
		break;
	}
	case APP_CMD_LOST_FOCUS:{
		if(engine_->_accelerometer != NULL){
			ASensorEventQueue_disableSensor(engine_->_sensorEventQueue, engine_->_accelerometer);
		}

		if(engine_->_gs)
			engine_->_gs->draw();
		engine_->_animate = false;
		break;
	}
	}
}

void android_main( struct android_app* application ){

	engine engine;

	app_dummy();

	const int32_t n = 400;
	Mat im(n, n, CV_8UC3, Scalar(0));

	LOGI(caption, "Android NDK test application ");

	memset(&engine, 0, sizeof(engine));
	application->userData = &engine;
	application->onAppCmd = engineHandleCmd;
	application->onInputEvent = engineHandleInput;
	engine._app = application;

	if(application->savedState != NULL){
		engine._state = *(saved_state*)application->savedState;
	}

	LOGI(caption, "start main loop");

	while(1){

		int ident;
		int event;
		android_poll_source* source;

		while( (ident = ALooper_pollAll( engine._animate ? 0 : -1, NULL, &event, (void**)&source)) >= 0 ){
			LOGI(caption, "event");
			if(source != NULL){
				source->process(application, source);
			}
			if(application->destroyRequested != 0){
				if(engine._gs){
					delete engine._gs; engine._gs = NULL;
				}
				return;
			}
		}
		if( engine._animate && engine._gs){
			LOGI(caption, "draw in main loop");
			engine._gs->draw();
		}
		LOGI(caption, "main loop");
	}
}













