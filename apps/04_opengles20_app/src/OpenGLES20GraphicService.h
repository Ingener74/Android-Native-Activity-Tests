/*
 * OpenGLES20GraphicService.h
 *
 *  Created on: 13.03.2013
 *      Author: pavel
 */

#ifndef OPENGLES20GRAPHICSERVICE_H_
#define OPENGLES20GRAPHICSERVICE_H_

#include <GLES2/gl2.h>
#include <EGL/egl.h>

#include <IGraphicsService.h>
#include <tools.h>

#include <ITexture.h>
#include <IObject.h>

#define LOGI_OGLES20GS(...){ LOGI("OpenGLES20GraphicService", __VA_ARGS__); }
#define LOGE_OGLES20GS(...){ LOGE("OpenGLES20GraphicService", __VA_ARGS__); }
#define LOGW_OGLES20GS(...){ LOGW("OpenGLES20GraphicService", __VA_ARGS__); }

class OpenGLES20GraphicService: public IGraphicsService{
public:
	typedef IGraphicsService::STATUS STATUS;

	OpenGLES20GraphicService();
	virtual ~OpenGLES20GraphicService();

	STATUS init( android_app* application );
	bool isInit();

	void deinit();

	void draw();

	void setImage( Mat image );

private:
	bool         _isInit;

	EGLDisplay   _display;
	EGLContext   _context;
	EGLSurface   _surface;

	EGLint       _width;
	EGLint       _height;

	GLuint       _program;
	GLuint       _vpos;
	GLuint       _atex;
	GLint        _stex;
	GLuint       _uortho;

	ITexture*    _tex1;
	IObject*     _tr1;

	static GLuint loadShader( GLenum shaderType, const char* source );
	static GLuint createProgram( const char* vertexShader, const char* fragmentShader );
};

#endif /* OPENGLES20GRAPHICSERVICE_H_ */
