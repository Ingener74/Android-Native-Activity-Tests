/*
 * IShaderProgram.h
 *
 *  Created on: 17.03.2013
 *      Author: pavel
 */

#ifndef ISHADERPROGRAM_H_
#define ISHADERPROGRAM_H_

#include <GLES2/gl2.h>
#include "ErrorHandler.h"

#include <tools.h>

class IShaderProgram: public ErrorHandler {
public:
	IShaderProgram(
			const char* vertexShaderSource,
			const char* fragmentShaderSource );
	virtual ~IShaderProgram();

	virtual void   useProgram(){ glUseProgram(_program); }
	virtual GLuint getProgram(){ return _program; }

	virtual GLuint getAttribute( const char* attr ){
		return glGetAttribLocation(_program, attr);
	}

	GLuint loadShader( GLenum shaderType, const char* source );
	GLuint createProgram( const char* vertexShader, const char* fragmentShader );

private:
	GLuint _vs;
	GLuint _fs;
	GLuint _program;
};

#endif /* ISHADERPROGRAM_H_ */
