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

#include "OpenGLESTestEventEngine.h"
#include "OpenGLES100GraphicsService.h"

using namespace cv;
using namespace std;

using namespace nae;
using namespace opengles_test;

const char* caption =
		"OpenGL ES 1.0 test application"
		;
void android_main( struct android_app* application ){

	LOGI("main", caption);

	IGraphicsService* opengles100 = new OpenGLES100GraphicsService();
	IEventEngine* sep = new OpenGLESTestEventEngine(application, opengles100);

	LOGI("main", "run");

	if(sep)
		sep->run();

	LOGI("main", "release resources");
	delete opengles100;
	delete sep;
}













