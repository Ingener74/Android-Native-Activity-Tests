/*
 * main.cpp
 *
 *  Created on: 25.01.2013
 *      Author: pavel
 */

#include <fstream>

#include <jni.h>
#include <errno.h>

#include <android/log.h>
#include <android/looper.h>
#include <android/sensor.h>
#include <android_native_app_glue.h>

#include <GLES/gl.h>
#include <EGL/egl.h>

using namespace std;

const char app_name[] = "sensors_list";
#define LOGI(...)(__android_log_print(ANDROID_LOG_INFO,  app_name, __VA_ARGS__))
#define LOGE(...)(__android_log_print(ANDROID_LOG_ERROR, app_name, __VA_ARGS__))
#define LOGD(...)(__android_log_print(ANDROID_LOG_DEBUG, app_name, __VA_ARGS__))
#define LOGW(...)(__android_log_print(ANDROID_LOG_WARN,  app_name, __VA_ARGS__))

struct saved_state{
};

struct engine{
	android_app*       _app;
	saved_state        _state;
};

int engineInitDisplay( engine* engine ){
	return 0;
}

void engineDrawFrame( engine* engine ){
}

void engineTermDisplay( engine* engine ){
}

static int32_t engineHandleInput( struct android_app* app, AInputEvent* event ){
	return 0;
}

static void engineHandleCmd( struct android_app* app, int32_t cmd){

	LOGI("handle command");

	engine* engine_ = (engine*)app->userData;

	switch(cmd){
	case APP_CMD_SAVE_STATE:{
		break;
	}
	case APP_CMD_INIT_WINDOW:{
		break;
	}
	case APP_CMD_TERM_WINDOW:{
		engineTermDisplay(engine_);
		break;
	}
	case APP_CMD_GAINED_FOCUS:{
		break;
	}
	case APP_CMD_LOST_FOCUS:{
		break;
	}
	}
}

const char* sensor_type_strings[12 + 1]	= {
		"NULL TYPE",
		"ASENSOR_TYPE_ACCELEROMETER",
		"ASENSOR_TYPE_MAGNETIC_FIELD",
		"SENSOR_TYPE_ORIENTATION",
		"ASENSOR_TYPE_GYROSCOPE",
		"ASENSOR_TYPE_LIGHT",
		"SENSOR_TYPE_PRESSURE",
		"SENSOR_TYPE_TEMPERATURE",
		"ASENSOR_TYPE_PROXIMITY",
		"SENSOR_TYPE_GRAVITY",
		"SENSOR_TYPE_LINEAR_ACCELERATION",
		"SENSOR_TYPE_ROTATION_VECTOR",
		"SENSOR_TYPE_RELATIVE_HUMIDITY"
};

void android_main( struct android_app* application ){

	engine engine;

	app_dummy();

	LOGI("Android NDK test application ");

	memset(&engine, 0, sizeof(engine));
	application->userData = &engine;
	application->onAppCmd = engineHandleCmd;
	application->onInputEvent = engineHandleInput;

	engine._app = application;

	ASensorManager* _asm = ASensorManager_getInstance();

	if(_asm){
		LOGI("asm is %d", _asm);

		ofstream sensor_out_file;
		sensor_out_file.open("/sdcard/avail_sensors.txt");
		if(sensor_out_file.is_open()){

			LOGI("file is open");

			ASensorList sl;
			int32_t numOfSensors = ASensorManager_getSensorList(_asm, &sl);

			if(sl){
				LOGI("num of sensors = %d", numOfSensors);

				sensor_out_file << "Your devices have " << numOfSensors << " sensors" << endl;

				for( int32_t i = 0; i < numOfSensors; ++i ){
					LOGI("sensor pointer is %d", sl[i]);
					if(sl[i])
						sensor_out_file << i <<
							". " << ASensor_getName( sl[i] ) << endl <<
							"    " << ASensor_getVendor(sl[i]) << endl <<
							"    " << sensor_type_strings[ASensor_getType(sl[i])] << endl <<
							"    " << ASensor_getResolution(sl[i]) << endl <<
							"    " << ASensor_getMinDelay(sl[i]) << endl;
					else{
						LOGE("cannot access to sensor: pointer is null");
						sensor_out_file << i <<
												". " << "pointer is null" << endl;
					}
				}
			}else{
				LOGE("sensor list pointer is %d", sl);
			}

		}else{
			LOGE("cannot open file");
		}
	}else{
		LOGE("can't get sensor manager");
	}


	if(application->savedState != NULL){
		engine._state = *(saved_state*)application->savedState;
	}

	LOGI("start main loop");

	while(1){

		int ident;
		int event;
		android_poll_source* source;

		while( (ident = ALooper_pollAll(-1, NULL, &event, (void**)&source)) >= 0 ){
			if(source != NULL){
				source->process(application, source);
			}

			if(application->destroyRequested != 0){
				engineTermDisplay(&engine);
				return;
			}
		}
	}
}













