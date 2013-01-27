/*
 * DroidBlaster.h
 *
 *  Created on: 26.01.2013
 *      Author: pavel
 */

#ifndef DROIDBLASTER_H_
#define DROIDBLASTER_H_

#include <unistd.h>
#include <android_native_app_glue.h>

#include "ActivityHandler.h"
#include "Types.hpp"
#include "Context.h"
#include "TimeService.h"

namespace smallarsdk {

class DroidBlaster: public ActivityHandler {

public:
	DroidBlaster( Context& context, android_app* application );
	virtual ~DroidBlaster();

protected:
	status onActivate();
	void   onDeactivate();
	status onStep();

	void   onStart();
	void   onResume(){}
	void   onPause(){}
	void   onStop(){}
	void   onDestroy(){}

	void   onSaveState(void **data, int32_t size){}
	void   onConfigurationChanged(){}
	void   onLowMemory(){}

	void   onCreateWindow(){}
	void   onDestroyWindow(){}
	void   onGainFocus(){}
	void   onLostFocus(){}

private:
	void clear();
	void drawCursor( int size, int pX, int pY );

private:
	android_app*          _application;
	ANativeWindow_Buffer  _windowBuffer;
	TimeService*          _timeService;

	bool _initialized;

	float _posX;
	float _posY;
	const int32_t _size;
	const float   _speed;
};

} /* namespace handtracker */
#endif /* DROIDBLASTER_H_ */
