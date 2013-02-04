/*
 * Test application for OpenGL
 */
#include <jni.h>
#include <errno.h>
#include <math.h>

#include <android/log.h>
#include <android/looper.h>
#include <android/sensor.h>
#include <android_native_app_glue.h>

#include <GLES/gl.h>
#include <EGL/egl.h>

#include "GraphicsService.h"

using namespace native_test_app_7;

const char* caption =
		"native_test_app_7"
		;

struct saved_state{
	float _accX;
	float _accY;
	float _accZ;
};

class Point3D{
public:
	union{
		double _v[3];
		struct{
			double _x;
			double _y;
			double _z;
		};
	};
	Point3D( double x = 0.0, double y = 0.0, double z = 0.0 ):
		_x(x), _y(y), _z(z){
	}
};
class Line3D{
	Point3D _start, _end;
public:
	Line3D( const Point3D& start = Point3D(), const Point3D end = Point3D()):
		_start(start), _end(end){
	}
	void draw(){
		GLfloat line[] = {
				_start._x, _start._y, _start._z,
				_end._x,   _end._y,   _end._z
		};
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, line);
		glDrawArrays(GL_LINES, 0, 2);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
};

class NativeTest8GS: public GraphicsService{
	saved_state* _saved_state;
public:
	NativeTest8GS( android_app* application ,saved_state* saved_state_ ):
		GraphicsService(application),
		_saved_state(saved_state_){
	}
	virtual ~NativeTest8GS(){}

	void draw(){
		if(_display != EGL_NO_DISPLAY && _saved_state != NULL ){
			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			GLfloat mag = sqrt(
					_saved_state->_accX*_saved_state->_accX +
					_saved_state->_accY*_saved_state->_accY +
					_saved_state->_accZ*_saved_state->_accZ);
			/*
			 * out green display
			 */
			Line3D(Point3D(), Point3D(1, 0, 0)).draw();
			Line3D(Point3D(), Point3D(0, 1, 0)).draw();
			Line3D(Point3D(), Point3D(0, 0, 1)).draw();

			Line3D(Point3D(),
					Point3D(_saved_state->_accX / mag,
							_saved_state->_accY / mag ,
							_saved_state->_accZ / mag)).draw();

			eglSwapBuffers(_display, _surface);
		}
	}
};

struct engine{
	android_app*       _app;
	ASensorManager*    _sensorMgr;
	const ASensor*     _accelerometer;
	ASensorEventQueue* _sensorEventQueue;

	NativeTest8GS*     _gs;

	saved_state        _state;
	bool               _animate;
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
			engine_->_gs = new NativeTest8GS(engine_->_app, &engine_->_state);
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

	LOGI(caption, "Android NDK test application ");

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
			if( ident == LOOPER_ID_USER ){
				if(engine._accelerometer != NULL){
					ASensorEvent event;
					while(ASensorEventQueue_getEvents(engine._sensorEventQueue, & event, 1) > 0){
						LOGI(caption, "accelerometer: x = %f, y = %f, z = %f",
								event.acceleration.x,
								event.acceleration.y,
								event.acceleration.z);
						engine._state._accX = event.acceleration.x;
						engine._state._accY = event.acceleration.y;
						engine._state._accZ = event.acceleration.z;
					}
				}
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













