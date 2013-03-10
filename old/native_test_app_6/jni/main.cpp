/*
 * main.cpp
 *
 *  Created on: 25.01.2013
 *      Author: pavel
 */

#include <jni.h>
#include <errno.h>

#include <android/log.h>
#include <android/looper.h>
#include <android/sensor.h>
#include <android_native_app_glue.h>

#include <GLES/gl.h>
#include <EGL/egl.h>

const char app_name[] = "native_test_app_6";
#define LOGI(...)(__android_log_print(ANDROID_LOG_INFO,  app_name, __VA_ARGS__))
#define LOGE(...)(__android_log_print(ANDROID_LOG_ERROR, app_name, __VA_ARGS__))
#define LOGD(...)(__android_log_print(ANDROID_LOG_DEBUG, app_name, __VA_ARGS__))
#define LOGW(...)(__android_log_print(ANDROID_LOG_WARN,  app_name, __VA_ARGS__))

struct saved_state{
	float   _angle;
	int32_t _x;
	int32_t _y;

	float _accX;
	float _accY;
	float _accZ;
};

struct engine{
	android_app*       _app;
	ASensorManager*    _sensorMgr;
	const ASensor*     _accelerometer;
	ASensorEventQueue* _sensorEventQueue;

	bool               _animate;
	EGLDisplay         _display;
	EGLSurface         _surface;
	EGLContext         _context;
	int32_t            _width;
	int32_t            _height;
	saved_state        _state;
};

int engineInitDisplay( engine* engine ){

	LOGI("init display");

	const EGLint attribs[] = {
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_BLUE_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_RED_SIZE, 8,
			EGL_NONE
	};

	EGLint w, h, dummy, format;
	EGLint numConf;
	EGLConfig config;
	EGLSurface surface;
	EGLContext context;

	EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	eglInitialize(display, 0, 0);

	eglChooseConfig(display, attribs, &config, 1, &numConf);

	eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

	ANativeWindow_setBuffersGeometry(engine->_app->window, 0, 0, format);

	surface = eglCreateWindowSurface(display, config, engine->_app->window, NULL);
	context = eglCreateContext(display, config, NULL, NULL);

	if(eglMakeCurrent(display, surface, surface, context) == EGL_FALSE){
		LOGE("Unable to eglMakeCurrent");
		return -1;
	}
	eglQuerySurface(display, surface, EGL_WIDTH, &w);
	eglQuerySurface(display, surface, EGL_HEIGHT, &h);

	engine->_display = display;
	engine->_context = context;
	engine->_surface = surface;
	engine->_height = h;
	engine->_width = w;
	engine->_state._angle = 0;

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glDisable(GL_DEPTH_TEST);

	LOGI("init display success");

	return 0;
}

void engineDrawFrame( engine* engine ){
	LOGI("draw frame");

	if(engine->_display == NULL){
		return;
	}

//	float r = float(engine->_state._x) / engine->_width;
//	float g = float(engine->_state._angle);
//	float b = float(engine->_state._y) / engine->_height;

	double sum =
			engine->_state._accX +
			engine->_state._accY +
			engine->_state._accZ;

	float r = engine->_state._accX / sum;
	float g = engine->_state._accY / sum;
	float b = engine->_state._accZ / sum;

	glClearColor(r, g, b, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	LOGI("draw color: r = %f, g = %f, b = %f", r, g, b);

	eglSwapBuffers(engine->_display, engine->_surface);
}

void engineTermDisplay( engine* engine ){
	if(engine->_display != EGL_NO_DISPLAY){
		eglMakeCurrent(engine->_display, engine->_surface, engine->_surface, engine->_context);
		if(engine->_context != EGL_NO_CONTEXT){
			eglDestroyContext(engine->_display, engine->_context);
		}
		if(engine->_surface != EGL_NO_SURFACE){
			eglDestroySurface(engine->_display, engine->_surface);
		}
		eglTerminate(engine->_display);
	}
	engine->_animate = false;
	engine->_display = EGL_NO_DISPLAY;
	engine->_context = EGL_NO_CONTEXT;
	engine->_surface = EGL_NO_SURFACE;
}

static int32_t engineHandleInput( struct android_app* app, AInputEvent* event ){

	LOGI("input handle");

	engine* engine_ = (engine*)app->userData;

	if(AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION){
		engine_->_animate = true;
		engine_->_state._x = AMotionEvent_getX(event, 0);
		engine_->_state._y = AMotionEvent_getY(event, 0);
		return 1;
	}
	return 0;
}

static void engineHandleCmd( struct android_app* app, int32_t cmd){

	LOGI("handle command");

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
			engineInitDisplay(engine_);
			engineDrawFrame(engine_);
		}
		break;
	}
	case APP_CMD_TERM_WINDOW:{
		engineTermDisplay(engine_);
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
		engine_->_animate = false;
		engineDrawFrame(engine_);
		break;
	}
	}
}

void android_main( struct android_app* application ){

	engine engine;

	app_dummy();

	LOGI("Android NDK test application ");

	memset(&engine, 0, sizeof(engine));
	application->userData = &engine;
	application->onAppCmd = engineHandleCmd;
	application->onInputEvent = engineHandleInput;
	engine._app = application;

	engine._sensorMgr = ASensorManager_getInstance();
	engine._accelerometer = ASensorManager_getDefaultSensor(engine._sensorMgr,
			ASENSOR_TYPE_ACCELEROMETER);
	engine._sensorEventQueue = ASensorManager_createEventQueue(
			engine._sensorMgr, application->looper, LOOPER_ID_USER, NULL, NULL);

//	LOGI("accel = %d", engine._accelerometer);

	if(application->savedState != NULL){
		engine._state = *(saved_state*)application->savedState;
	}

	LOGI("start main loop");

	while(1){

		int ident;
		int event;
		android_poll_source* source;

		while( (ident = ALooper_pollAll(engine._animate ? 0 : -1, NULL, &event, (void**)&source)) >= 0 ){
			if(source != NULL){
				source->process(application, source);
			}

			if( ident == LOOPER_ID_USER ){
				if(engine._accelerometer != NULL){
					ASensorEvent event;
					while(ASensorEventQueue_getEvents(engine._sensorEventQueue, & event, 1) > 0){
//						LOGI("accelerometer: x = %f, y = %f, z = %f",
//								event.acceleration.x,
//								event.acceleration.y,
//								event.acceleration.z);
						engine._state._accX = event.acceleration.x;
						engine._state._accY = event.acceleration.y;
						engine._state._accZ = event.acceleration.z;
					}
				}
			}

			if(application->destroyRequested != 0){
				engineTermDisplay(&engine);
				return;
			}
		}

//		if(engine._animate)
		{
			engine._state._angle += .01f;
			if(engine._state._angle > 1){
				engine._state._angle = 0;
			}
			engineDrawFrame(&engine);
		}
	}
}













