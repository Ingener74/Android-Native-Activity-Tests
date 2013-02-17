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

#include "SimpleEventProcessor.h"

using namespace cv;
using namespace std;

using namespace nae;

const char* caption =
		"Android native-activity fish bone application"
		;
void android_main( struct android_app* application ){

	LOGI("main", caption);

	SimpleEventProcessor* sep = new SimpleEventProcessor(application);
	sep->run();

}













