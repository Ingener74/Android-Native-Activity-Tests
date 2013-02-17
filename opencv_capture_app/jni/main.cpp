/*
 * Test application for OpenGL
 */

#include <fstream>
#include <string>

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
#include <opencv2/imgproc/imgproc.hpp>

#include "GraphicsService.h"

#include "GLTriangle.h"
#include "RGBTexture.h"

using namespace native_test_app_8;
using namespace cv;
using namespace std;

const char* caption =
		"OpenCV VideoCapture native-activity application"
		;

Mat texim;
const int32_t tex_side = 1024; //512;

//const int32_t cam_w = 640, cam_h = 480;
const int32_t cam_w = 864, cam_h = 480;

const GLfloat side = 500;
GLfloat screenSqruare[] = {
		0,      0,      0,
		cam_w,  0,      0,
		cam_w, -cam_h,  0,
		0,     -cam_h,  0
};
GLfloat texcoords[] = {
		0.f,                       0.f,
		cam_w / GLfloat(tex_side), 0.f,
		cam_w / GLfloat(tex_side), cam_h / GLfloat(tex_side),
		0.f,                       cam_h / GLfloat(tex_side)
};
GLfloat colors[] = {
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
};
GLushort indexes[] = {
		0, 2, 1,
		2, 0, 3
};


RGBTexture* mt = 0;
IObject*  tr = 0;

VideoCapture vc;
bool vc_init = false;
Mat videoInput;

/*
 * fps
 */
const int fps30_delay = 1000 / 30;

struct saved_state{
};

class OpenCVVideoCaptureGS: public GraphicsService{
	saved_state* _saved_state;
public:
	OpenCVVideoCaptureGS( android_app* application ,saved_state* saved_state_ ):
		GraphicsService(application),
		_saved_state(saved_state_){
	}
	virtual ~OpenCVVideoCaptureGS(){}

	void draw(){
		if(_display != EGL_NO_DISPLAY && _saved_state != NULL ){
			glEnable(GL_TEXTURE_2D);
			glClearColor(0.f, 0.f, 0.f, 1);
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

			/*
			 * draw custom scene
			 */
			if(vc.isOpened()){
				vc >> videoInput;
				if(videoInput.rows && videoInput.cols)
					cvtColor(videoInput, videoInput, CV_RGB2BGR);
				LOGI("gs draw", "frame input");
			}

			if(mt && videoInput.cols && videoInput.rows &&
					videoInput.cols <= tex_side &&
					videoInput.rows <= tex_side ){
				mt->updatePart(videoInput);
				LOGI("gs draw", "frame updated");
			}else{
				LOGE("gs draw", "frame update error, vr = %d, vc = %d",
						videoInput.rows, videoInput.cols);
			}

			if(tr){
				tr->draw();
				LOGI("gs draw", "frame draw");
			}

			glDisable(GL_TEXTURE_2D);
			eglSwapBuffers(_display, _surface);
		}
	}
};

struct engine{
	android_app*       _app;
	ASensorManager*    _sensorMgr;
	const ASensor*     _accelerometer;
	ASensorEventQueue* _sensorEventQueue;

	OpenCVVideoCaptureGS*     _gs;

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
			engine_->_gs = new OpenCVVideoCaptureGS(engine_->_app, &engine_->_state);
			engine_->_animate = true;
			LOGI("init window", "end init window");


			LOGI("init window", "create objects begin");

			vc = VideoCapture(CV_CAP_ANDROID + 0);
			if(!vc.isOpened()){
				vc_init = false;
//				delete vc; vc = 0;
				LOGI("init window", "capture device is not opened");
			}else{
				vc.set(CV_CAP_PROP_FRAME_WIDTH, cam_w);
				vc.set(CV_CAP_PROP_FRAME_HEIGHT, cam_h);

//				vc.set(CV_CAP_PROP_FRAME_WIDTH, 320);
//				vc.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

				vc_init = true;
				LOGI("init window", "capture device is opened");
			}
			texim = Mat(tex_side, tex_side, CV_8UC3, Scalar(0, 80, 30));

			mt = new RGBTexture(texim);
			tr = new GLTriangle(mt, screenSqruare, texcoords, colors,
					indexes, 6);

			LOGI("init window", "create objects end");
		}
		break;
	}
	case APP_CMD_TERM_WINDOW:{
		LOGI("native_test_app_7", "terminate window");
		delete engine_->_gs; engine_->_gs = NULL;
		engine_->_animate = false;

		vc.release();
		break;
	}
	case APP_CMD_GAINED_FOCUS:{
		break;
	}
	case APP_CMD_LOST_FOCUS:{
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

	LOGI("main", caption);

	memset(&engine, 0, sizeof(engine));
	application->userData = &engine;
	application->onAppCmd = engineHandleCmd;
	application->onInputEvent = engineHandleInput;

	engine._app = application;

	if(application->savedState != NULL){
		engine._state = *(saved_state*)application->savedState;
	}

	LOGI("main", "start main loop");

	while(1){

		int ident;
		int event;
		android_poll_source* source;

		while( (ident = ALooper_pollAll( engine._animate ? fps30_delay : -1, NULL, &event, (void**)&source)) >= 0 ){
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
		LOGI("main", "main loop");
	}
}













