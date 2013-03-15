
#include <android_native_app_glue.h>
#include <tools.h>

#include "OpenGLES20EventHandler.h"
#include "OpenGLES20GraphicService.h"

const char* caption =
		"Android Native-Activity OpenCV capture application"
		;

void android_main( android_app* app ){

	LOGI("android main", caption);

	OpenGLES20GraphicService gs = OpenGLES20GraphicService();

	OpenGLES20EventHandler eh(app, &gs);
	eh.run();
}
