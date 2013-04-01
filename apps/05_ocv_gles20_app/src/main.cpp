
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

	ICaptureService* cs = new OpenCVCapture();
//	if(cs->isError()){
//		LOGE("android main", "could not create capture service");
//		exit(EXIT_FAILURE);
//	}

	IGraphicsService* gs = new OpenGLES20GraphicService();

	OpenGLES20EventHandler eh(app, gs, cs);
	eh.run();
}
