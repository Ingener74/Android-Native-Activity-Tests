/*
 * Test application for OpenGL
 */

#include "OpenGLES100GraphicsService.h"
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

	IGraphicsService* gs  = new OpenGLES100GraphicsService();
	IEventEngine*     sep = new OpenGLESTestEventEngine(application, gs);

	LOGI("main", "run");
	if(sep)
		sep->run();

	LOGI("main", "release resources");
	delete sep;
	delete gs;
}
