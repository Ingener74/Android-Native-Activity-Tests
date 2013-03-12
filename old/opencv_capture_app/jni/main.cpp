/*
 * Test application for OpenGL
 */

#include "OpenCVCapture.h"
#include "NullCapture.h"

#include "OpenGLES100OpenCVVisualizer.h"

#include "OpenCVEvent.h"

#include "tools.h"

const char* caption =
		"OpenCV VideoCapture native-activity application"
		;

void android_main( struct android_app* application ){

	LOGI("android main", "begin");

	ICaptureService*  cs   = new NullCapture();
	IGraphicsService* gs   = new OpenGLES100_OpenCVVisualizer();
	IEventEngine*     ocve = new OpenCVEvent(application, gs, cs);

	if(ocve)
		ocve->run();

	delete ocve; ocve = 0;
	delete gs; gs = 0;

	LOGI("android main", "begin");
}