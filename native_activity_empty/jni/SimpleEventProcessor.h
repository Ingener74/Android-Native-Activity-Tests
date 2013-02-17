/*
 * SimpleEventProcessor.h
 *
 *  Created on: 17.02.2013
 *      Author: pavel
 */

#ifndef SIMPLEEVENTPROCESSOR_H_
#define SIMPLEEVENTPROCESSOR_H_

#include "IEventEngine.h"

namespace nae {

#define LOGI_SEP(...){ LOGI("SimpleEventProcessor", __VA_ARGS__)}

class SimpleEventProcessor: public IEventEngine {
public:
	SimpleEventProcessor( android_app* application );
	virtual ~SimpleEventProcessor();

	virtual void run();

	virtual void onInitWindow();
	virtual void onTermWindow();
};

} /* namespace nae */
#endif /* SIMPLEEVENTPROCESSOR_H_ */
