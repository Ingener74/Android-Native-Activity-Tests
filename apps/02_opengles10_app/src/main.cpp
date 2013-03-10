

#include <android_native_app_glue.h>
#include <tools.h>

#include "OpenGLES10EventHandler.h"

#include "OpenGLES10GraphicsService.h"

const char* caption =
		"Android Native-Activity OpenGL ES 1.0 application"
		;

void android_main( android_app* app ){

	LOGI("android main", caption);

	IGraphicsService* gs = new OpenGLES10GraphicsService();

	OpenGLES10EventHandler* eh = new OpenGLES10EventHandler(app, gs);

	if(eh)
		eh->run();
}
