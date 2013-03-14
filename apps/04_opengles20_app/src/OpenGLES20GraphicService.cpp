/*
 * OpenGLES20GraphicService.cpp
 *
 *  Created on: 13.03.2013
 *      Author: pavel
 */

#include "OpenGLES20GraphicService.h"

OpenGLES20GraphicService::OpenGLES20GraphicService(): _isInit(false) {
}

OpenGLES20GraphicService::~OpenGLES20GraphicService() {
}

OpenGLES20GraphicService::STATUS OpenGLES20GraphicService::init(
		android_app* application ){



	_isInit = true;
	return STATUS_OK;
}
bool OpenGLES20GraphicService::isInit(){
	return false;
}

void OpenGLES20GraphicService::deinit(){

}

void OpenGLES20GraphicService::draw(){

}

void OpenGLES20GraphicService::setImage( const Mat& image ){

}

GLuint OpenGLES20GraphicService::loadShader( GLenum shaderType, const char* source ){
	GLuint shader = glCreateShader(shaderType);
	if(shader){
		glShaderSource(shader, 1, &source, 0);
		glCompileShader(shader);

		GLint compiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if(!compiled){
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
			if(infoLen){
				char* buf = new char[infoLen];
				if(buf){
					glGetShaderInfoLog(shader, infoLen, 0, buf);
					LOGE("loadShader", "Could not compile shader: %d,\n%s", shaderType, buf);
					delete buf;
				}
				glDeleteShader(shader);
				shader = 0;
			}
		}
	}
	return shader;
}

GLuint OpenGLES20GraphicService::createProgram( const char* vertexShader, const char* fragmentShader ){
	GLuint vs = loadShader(GL_VERTEX_SHADER, vertexShader);
	if(!vs){
		return 0;
	}
	GLuint fs = loadShader(GL_FRAGMENT_SHADER, fragmentShader);
	if(!fs){
		return 0;
	}

	GLuint program = glCreateProgram();
	if(program){
		glAttachShader(program, vs); GLERR;
		glAttachShader(program, fs); GLERR;

		glLinkProgram(program);
		GLint linkStatus = GL_FALSE;
		glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
		if(linkStatus != GL_TRUE){
			GLint bufLen = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLen);
			if(bufLen){
				char* buf = (char*)new char[bufLen];
				if(buf){
					glGetProgramInfoLog(program, bufLen, NULL, buf);
					LOGE_OGLES20GS("Could not link program");
					delete [] buf;
				}
			}
			glDeleteProgram(program);
			program = 0;
		}
	}
	return program;
}
