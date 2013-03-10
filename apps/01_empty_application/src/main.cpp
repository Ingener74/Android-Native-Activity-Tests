

#include <android_native_app_glue.h>
#include <tools.h>

#include "EmptyAppEventHandler.h"

const char* caption =
		"Android Native-Activity empty application"
		;

void android_main( android_app* application ){

	LOGI("android main", caption);

	EmptyAppEventHandler* ah = new EmptyAppEventHandler(application);

	if(ah)
		ah->run();
	else
		LOGE("android main", "Empty application event handler: "
				"error can't allocate memory");
}
