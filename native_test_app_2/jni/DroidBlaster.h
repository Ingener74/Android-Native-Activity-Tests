/*
 * DroidBlaster.h
 *
 *  Created on: 26.01.2013
 *      Author: pavel
 */

#ifndef DROIDBLASTER_H_
#define DROIDBLASTER_H_

#include "ActivityHandler.h"
#include "Types.hpp"

#include <unistd.h>

namespace smallarsdk {

class DroidBlaster: public ActivityHandler {

public:
	DroidBlaster();
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
};

} /* namespace handtracker */
#endif /* DROIDBLASTER_H_ */
