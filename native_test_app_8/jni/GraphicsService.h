/*
 * GraphicsService.h
 *
 *  Created on: 03.02.2013
 *      Author: pavel
 */

#ifndef GRAPHICSSERVICE_H_
#define GRAPHICSSERVICE_H_

#include <GLES/gl.h>
#include <EGL/egl.h>
#include <android_native_app_glue.h>

#include "tools.h"

namespace native_test_app_7 {

class GraphicsService {
public:
	GraphicsService( android_app* application );
	virtual ~GraphicsService();

	void init( android_app* application );
	void deinit();

	const EGLint& getWidth()  const { return _width;  }
	const EGLint& getHeight() const { return _height; }

	virtual void draw() = 0;

protected:
	EGLDisplay  _display;
	EGLContext  _context;
	EGLSurface  _surface;

	EGLint      _width;
	EGLint      _height;
};

} /* namespace native_test_app_7 */
#endif /* GRAPHICSSERVICE_H_ */
