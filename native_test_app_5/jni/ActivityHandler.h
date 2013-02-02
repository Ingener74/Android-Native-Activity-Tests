/*
 * ActivityHandler.h
 *
 *  Created on: 26.01.2013
 *      Author: pavel
 */

#ifndef ACTIVITYHANDLER_H_
#define ACTIVITYHANDLER_H_

#include "Types.hpp"

namespace smallarsdk {

class ActivityHandler {
public:
	virtual ~ActivityHandler(){}
	virtual status onActivate() = 0;
	virtual void onDeactivate() = 0;
	virtual status onStep() = 0;

	virtual void onStart(){}
	virtual void onResume(){}
	virtual void onPause(){}
	virtual void onStop(){}
	virtual void onDestroy(){}

	virtual void onSaveState(void **_data, int32_t* _size){}
	virtual void onConfigurationChanged(){}
	virtual void onLowMemory(){}

	virtual void onCreateWindow(){}
	virtual void onDestroyWindow(){}
	virtual void onGainFocus(){}
	virtual void onLostFocus(){}
};

} /* namespace handtracker */
#endif /* ACTIVITYHANDLER_H_ */
