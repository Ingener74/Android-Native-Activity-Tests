/*
 * Test application for OpenGL
 */

#include "OpenCVEvent.h"
#include "OpenGLES100OpenCVVisualizer.h"

#include "tools.h"

const char* caption =
		"OpenCV VideoCapture native-activity application"
		;

void android_main( struct android_app* application ){

	LOGI("android main", "begin");

	IGraphicsService* gs = new OpenGLES100_OpenCVVisualizer();
	IEventEngine* ocve = new OpenCVEvent(application, gs);

	if(ocve)
		ocve->run();

	delete ocve; ocve = 0;
	delete gs; gs = 0;

	LOGI("android main", "begin");
}
