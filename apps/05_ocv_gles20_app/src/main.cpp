
#include <android_native_app_glue.h>
#include <tools.h>

#include "OpenGLES20EventHandler.h"
#include "OpenGLES20GraphicService.h"

#include <OpenCVCapture.h>
#include <CopyProcessor.h>

const char* caption =
		"Android Native-Activity OpenCV capture OpenGL ES 2.0 application"
		;

void android_main( android_app* app ){

	LOGI("android main", caption);

	ICaptureService* cs = new OpenCVCapture();

	IGraphicsService* gs = new OpenGLES20GraphicService();

	IProcessor* ps = new CopyProcessor(cs, gs);

	OpenGLES20EventHandler eh(app, gs, ps);
	eh.addService(cs);

	eh.run();
}
