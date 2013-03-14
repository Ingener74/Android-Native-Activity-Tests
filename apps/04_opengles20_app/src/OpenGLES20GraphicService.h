/*
 * OpenGLES20GraphicService.h
 *
 *  Created on: 13.03.2013
 *      Author: pavel
 */

#ifndef OPENGLES20GRAPHICSERVICE_H_
#define OPENGLES20GRAPHICSERVICE_H_

#include <GLES2/gl2.h>

#include <IGraphicsService.h>
#include <tools.h>

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

	void setImage( const Mat& image );

private:
	bool _isInit;

	static GLuint loadShader( GLenum shaderType, const char* source );
	static GLuint createProgram( const char* vertexShader, const char* fragmentShader );
};

#endif /* OPENGLES20GRAPHICSERVICE_H_ */
