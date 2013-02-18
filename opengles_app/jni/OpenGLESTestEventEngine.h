/*
 * OpenGLESTestEventEngine.h
 *
 *  Created on: Feb 18, 2013
 *      Author: ingener
 */

#ifndef OPENGLESTESTEVENTENGINE_H_
#define OPENGLESTESTEVENTENGINE_H_

#include "tools.h"

#include "IEventEngine.h"
#include "IGraphicsService.h"

#define LOGI_OGLESEE(...){ LOGI("OpenGLESTestEventEngine", __VA_ARGS__); }

using namespace nae;

namespace opengles_test {

class OpenGLESTestEventEngine: public IEventEngine {
public:
	OpenGLESTestEventEngine( android_app* application, IGraphicsService* graphicsService );
	virtual ~OpenGLESTestEventEngine();

	virtual void run();

	virtual void onInitWindow();
	virtual void onTermWindow();

protected:
	IGraphicsService* _graphicsService;
	bool              _animateGraphics;
};

} /* namespace opengles_test */
#endif /* OPENGLESTESTEVENTENGINE_H_ */
