/*
 * IShaderProgram.cpp
 *
 *  Created on: 17.03.2013
 *      Author: pavel
 */

#include "IShaderProgram.h"

IShaderProgram::IShaderProgram(
		const char* vertexShaderSource,
		const char* fragmentShaderSource ){

	_program = createProgram(vertexShaderSource, fragmentShaderSource);

}

IShaderProgram::~IShaderProgram() {
	glDeleteProgram(_program);
}

GLuint IShaderProgram::loadShader( GLenum shaderType, const char* source ){
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

GLuint IShaderProgram::createProgram( const char* vertexShader, const char* fragmentShader ){
	_vs = loadShader(GL_VERTEX_SHADER, vertexShader);
	if(!_vs){
		return 0;
	}
	_fs = loadShader(GL_FRAGMENT_SHADER, fragmentShader);
	if(!_fs){
		return 0;
	}

	GLuint program = glCreateProgram();
	if(program){
		glAttachShader(program, _vs);
		glAttachShader(program, _fs);

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
					setError("could not link program");
					delete [] buf;
				}
			}
			glDeleteProgram(program);
			program = 0;
		}
	}
	return program;
}
