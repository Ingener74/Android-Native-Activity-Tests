/*
 * GLMatrix4x4.h
 *
 *  Created on: 15.03.2013
 *      Author: pavel
 */

#ifndef GLMATRIX4X4_H_
#define GLMATRIX4X4_H_

#include <GLES2/gl2.h>
#include <math.h>

class GLMatrix4x4{
public:

	GLMatrix4x4();
	GLMatrix4x4(
			GLfloat left, GLfloat right,
			GLfloat top,  GLfloat bottom,
			GLfloat near, GLfloat far);

	GLMatrix4x4(
			GLfloat near,        GLfloat far,
			GLfloat angleOfView, GLfloat aspectRatio);

	GLMatrix4x4( const GLfloat* matrix );

	virtual ~GLMatrix4x4(){}

	GLMatrix4x4& position(GLfloat x, GLfloat y, GLfloat z);
	GLMatrix4x4& move(GLfloat dx, GLfloat dy, GLfloat dz);

	GLMatrix4x4& scale(GLfloat x, GLfloat y, GLfloat z);
	GLMatrix4x4& resize(GLfloat dx, GLfloat dy, GLfloat dz);

	GLMatrix4x4& rotateX(GLfloat rad);
	GLMatrix4x4& rotateY(GLfloat rad);
	GLMatrix4x4& rotateZ(GLfloat rad);

	const GLfloat* getMatrix() const { return _m; }

private:
	GLfloat _m[16];
};

GLMatrix4x4 operator*( const GLMatrix4x4& m1, const GLMatrix4x4& m2 );

#endif /* GLMATRIX4X4_H_ */
