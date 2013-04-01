/*
 * SimpleShaderProgram.h
 *
 *  Created on: 17.03.2013
 *      Author: pavel
 */

#ifndef SIMPLESHADERPROGRAM_H_
#define SIMPLESHADERPROGRAM_H_

#include <GLES2/gl2.h>

#include "IShaderProgram.h"

class SimpleShaderProgram: public ShaderProgram {
public:
	SimpleShaderProgram(
			const char* vertexShaderSource,
			const char* fragmentShaderSouce );
	virtual ~SimpleShaderProgram();

	void useProgram();

private:
	GLuint _program;
};

#endif /* SIMPLESHADERPROGRAM_H_ */
