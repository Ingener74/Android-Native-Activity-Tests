/*
 * GLMatrix4x4.cpp
 *
 *  Created on: 15.03.2013
 *      Author: pavel
 */

#include "GLMatrix4x4.h"

/*
 * model view matrix
 */
GLMatrix4x4::GLMatrix4x4(){

	_m[0]  = 1.0; _m[1]  = 0.0; _m[2]  = 0.0; _m[3]  = 0.0;
	_m[4]  = 0.0; _m[5]  = 1.0; _m[6]  = 0.0; _m[7]  = 0.0;
	_m[8]  = 0.0; _m[9]  = 0.0; _m[10] = 1.0; _m[11] = 0.0;
	_m[12] = 0.0; _m[13] = 0.0; _m[14] = 0.0; _m[15] = 1.0;
}
GLMatrix4x4::GLMatrix4x4(GLfloat left, GLfloat right,
		GLfloat top, GLfloat bottom,
		GLfloat near, GLfloat far){

	_m[0] = 2.0 / (right - left);
	_m[1] = 0.f;
	_m[2] = 0.f;
	_m[3] = 0.f;

	_m[4] = 0.f;
	_m[5] = 2.f / (top - bottom);
	_m[6] = 0.f;
	_m[7] = 0.f;

	_m[8] = 0.f;
	_m[9] = 0.f;
	_m[10] = -2.0 / (far - near);
	_m[11] = 0.f;

	_m[12] = - (right + left) / (right - left);
	_m[13] = - (top + bottom) / (top - bottom);
	_m[14] = - (far + near) / (far - near);
	_m [15] = 1.f;
}
GLMatrix4x4::GLMatrix4x4(GLfloat near, GLfloat far,
			GLfloat angleOfView, GLfloat aspectRatio){

	GLfloat size = near * tanf(angleOfView / 2.0);
	GLfloat left   = -size;
	GLfloat right  = size;
	GLfloat bottom = -size / aspectRatio;
	GLfloat top    =  size / aspectRatio;

	_m[0] = 2 * near / (right - left);
	_m[1] = 0.f;
	_m[2] = 0.f;
	_m[3] = 0.f;

	_m[4] = 0.f;
	_m[5] = 2 * near / (top - bottom);
	_m[6] = 0.f;
	_m[7] = 0.f;

	_m[8] = (right + left)/(right - left);
	_m[9] = (top + bottom)/(top - bottom);
	_m[10] = -(far + near)/(far - near);
	_m[11] = -1.f;

	_m[12] = 0.f;
	_m[13] = 0.f;
	_m[14] = -(2 * far * near)/(far - near);
	_m[15] = 0.f;
}

GLMatrix4x4::GLMatrix4x4( const GLfloat* m ){
	_m[0]  = m[0];
	_m[1]  = m[1];
	_m[2]  = m[2];
	_m[3]  = m[3];

	_m[4]  = m[4];
	_m[5]  = m[5];
	_m[6]  = m[6];
	_m[7]  = m[7];

	_m[8]  = m[8];
	_m[9]  = m[9];
	_m[10] = m[10];
	_m[11] = m[11];

	_m[12] = m[12];
	_m[13] = m[13];
	_m[14] = m[14];
	_m[15] = m[15];
}

GLMatrix4x4& GLMatrix4x4::position(GLfloat x, GLfloat y, GLfloat z){
	_m[12] = x; _m[13] = y; _m[14] = z;
	return *this;
}
GLMatrix4x4& GLMatrix4x4::move(GLfloat dx, GLfloat dy, GLfloat dz){
	_m[12] += dx; _m[13] += dy; _m[14] += dz;
	return *this;
}
GLMatrix4x4& GLMatrix4x4::scale(GLfloat x, GLfloat y, GLfloat z){
	_m[0]  = x;
	_m[5]  = y;
	_m[10] = z;
	return *this;
}
GLMatrix4x4& GLMatrix4x4::resize(GLfloat dx, GLfloat dy, GLfloat dz){
	_m[0]  *= dx;
	_m[5]  *= dy;
	_m[10] *= dz;
	return *this;
}
GLMatrix4x4& GLMatrix4x4::rotateX(GLfloat rad){
	_m[5] = cosf(rad); _m[6] = -sinf(rad);
	_m[9] = -_m[6];    _m[10] = _m[5];
	return *this;
}
GLMatrix4x4& GLMatrix4x4::rotateY(GLfloat rad){
	_m[0] = cosf(rad); _m[2] = sinf(rad);
	_m[8] = -_m[2];    _m[10] = _m[0];
	return *this;
}
GLMatrix4x4& GLMatrix4x4::rotateZ(GLfloat rad){
	_m[0] = cosf(rad);  _m[1] = sinf(rad);
	_m[4] = -_m[1];     _m[5] = _m[0];
	return *this;
}
GLMatrix4x4 operator*( const GLMatrix4x4& mvm1, const GLMatrix4x4& mvm2 ){

	const GLfloat* m1 = mvm1.getMatrix();
	const GLfloat* m2 = mvm2.getMatrix();

	GLfloat m[16];

	m[0]  = m1[0]*m2[0]  + m1[4]*m2[1]  + m1[8] *m2[2]  + m1[12]*m2[3];
	m[1]  = m1[1]*m2[0]  + m1[5]*m2[1]  + m1[9] *m2[2]  + m1[13]*m2[3];
	m[2]  = m1[2]*m2[0]  + m1[6]*m2[1]  + m1[10]*m2[2]  + m1[14]*m2[3];
	m[3]  = m1[3]*m2[0]  + m1[7]*m2[1]  + m1[11]*m2[2]  + m1[15]*m2[3];

	m[4]  = m1[0]*m2[4]  + m1[4]*m2[5]  + m1[8] *m2[6]  + m1[12]*m2[7];
	m[5]  = m1[1]*m2[4]  + m1[5]*m2[5]  + m1[9] *m2[6]  + m1[13]*m2[7];
	m[6]  = m1[2]*m2[4]  + m1[6]*m2[5]  + m1[10]*m2[6]  + m1[14]*m2[7];
	m[7]  = m1[3]*m2[4]  + m1[7]*m2[5]  + m1[11]*m2[6]  + m1[15]*m2[7];

	m[8]  = m1[0]*m2[8]  + m1[4]*m2[9]  + m1[8] *m2[10] + m1[12]*m2[11];
	m[9]  = m1[1]*m2[8]  + m1[5]*m2[9]  + m1[9] *m2[10] + m1[13]*m2[11];
	m[10] = m1[2]*m2[8]  + m1[6]*m2[9]  + m1[10]*m2[10] + m1[14]*m2[11];
	m[11] = m1[3]*m2[8]  + m1[7]*m2[9]  + m1[11]*m2[10] + m1[15]*m2[11];

	m[12] = m1[0]*m2[12] + m1[4]*m2[13] + m1[8] *m2[14] + m1[12]*m2[15];
	m[13] = m1[1]*m2[12] + m1[5]*m2[13] + m1[9] *m2[14] + m1[13]*m2[15];
	m[14] = m1[2]*m2[12] + m1[6]*m2[13] + m1[10]*m2[14] + m1[14]*m2[15];
	m[15] = m1[3]*m2[12] + m1[7]*m2[13] + m1[11]*m2[14] + m1[15]*m2[15];

	return GLMatrix4x4(m);
}






