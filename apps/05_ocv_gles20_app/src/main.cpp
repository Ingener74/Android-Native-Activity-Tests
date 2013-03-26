
#include <android_native_app_glue.h>
#include <tools.h>

#include "OpenGLES20EventHandler.h"
#include "OpenGLES20GraphicService.h"

#include <OpenCVCapture.h>

const char* caption =
		"Android Native-Activity OpenCV capture OpenGL ES 2.0 application"
		;

void android_main( android_app* app ){

	LOGI("android main", caption);

	OpenCVCapture ocv_cam;

	OpenGLES20GraphicService gs = OpenGLES20GraphicService();

	OpenGLES20EventHandler eh(app, &gs, &ocv_cam);
	eh.run();
}
