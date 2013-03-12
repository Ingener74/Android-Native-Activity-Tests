
#include <android_native_app_glue.h>
#include <tools.h>

#include "OpenCVCapture.h"

#include "OpenCVCaptureGraphicsService.h"

#include "CopyProcessor.h"

#include "OpenCVCaptureEventHandler.h"


const char* caption =
		"Android Native-Activity OpenCV capture application"
		;

void android_main( android_app* app ){

	LOGI("android main", caption);

	ICaptureService* cs = new OpenCVCapture();

	OpenCVCaptureGraphicsService* gs = new OpenCVCaptureGraphicsService();

	IProcessor* ps = new CopyProcessor(cs, gs);

	OpenCVCaptureEventHandler* eh = new OpenCVCaptureEventHandler(app, gs, ps);

	if(eh)
		eh->run();
}
