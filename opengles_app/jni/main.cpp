/*
 * Test application for OpenGL
 */


#include <android/log.h>
#include <android_native_app_glue.h>

#include "NullCapture.h"
#include "OpenCVCapture.h"

//#include "CircleProcessor.h"

#include "OpenGLES100GraphicsService.h"
//#include "NativeWindowGraphicsService.h"

#include "OpenGLESTestEventEngine.h"

using namespace cv;
using namespace std;

using namespace nae;
using namespace opengles_test;

const char* caption =
		"OpenGL ES 1.0 test application"
		;
void android_main( struct android_app* application ){

	LOGI("main", caption);

//	ICaptureService*  cs = 0;
//	int j = 1;
//	if(j == 0){
//		cs = new NullCapture();
//	}else{
//		cs = new OpenCVCapture(0);
//	}

//	IProcessor* ps = 0;
//	int32_t n = 0;
//	if(n == 0){
//		ps = new CircleProcessor(cs);
//	}

	IGraphicsService* gs = 0;
//	int i = 1;
//	if(i == 0){
//		gs = new NativeWindowGraphicsService(cs);
//	}else if(i == 1){
		gs = new OpenGLES100GraphicsService();
//	}else{
//	}

	IEventEngine* sep = new OpenGLESTestEventEngine(application, gs);

	LOGI("main", "run");

//	if(sep)
//		sep->run();

	LOGI("main", "release resources");
//	delete opengles100;
//	delete sep;
}













