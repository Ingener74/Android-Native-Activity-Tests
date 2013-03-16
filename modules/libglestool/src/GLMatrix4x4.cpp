/*
 * GLMatrix4x4.cpp
 *
 *  Created on: 15.03.2013
 *      Author: pavel
 */

#include "GLMatrix4x4.h"

GLMatrix4x4::GLMatrix4x4() {
}

GLMatrix4x4::~GLMatrix4x4() {
}

void GLMatrix4x4::matrixIdentity( GLfloat* m ){

	m[0]  = 1.0; m[1]  = 0.0; m[2]  = 0.0; m[3]  = 0.0;
	m[4]  = 0.0; m[5]  = 1.0; m[6]  = 0.0; m[7]  = 0.0;
	m[8]  = 0.0; m[9]  = 0.0; m[10] = 1.0; m[11] = 0.0;
	m[12] = 0.0; m[13] = 0.0; m[14] = 0.0; m[15] = 1.0;
}

void GLMatrix4x4::matrixPosition( GLfloat* m, GLfloat x, GLfloat y, GLfloat z ){
	m[12] = x; m[13] = y; m[14] = z;
}

void GLMatrix4x4::matrixMove( GLfloat* m, GLfloat x, GLfloat y, GLfloat z ){
	m[12] += x; m[13] += y; m[14] += z;
}

void GLMatrix4x4::matrixScale( GLfloat* m, GLfloat x, GLfloat y, GLfloat z ){
	m[0] = x;
	m[5] = y;
	m[10] = z;
}

void GLMatrix4x4::matrixResize( GLfloat* m, GLfloat dx, GLfloat dy, GLfloat dz ){
	m[0]  *= dx;
	m[5]  *= dy;
	m[10] *= dz;
}

void GLMatrix4x4::matrixRotationX( GLfloat* m, GLfloat ar ){
	m[5] = cosf(ar); m[6] = -sinf(ar);
	m[9] = -m[6];    m[10] = m[5];
}
void GLMatrix4x4::matrixRotationY( GLfloat* m, GLfloat ar ){
	m[0] = cosf(ar); m[2] = sinf(ar);
	m[8] = -m[2];    m[10] = m[0];
}
void GLMatrix4x4::matrixRotationZ( GLfloat* m, GLfloat ar ){
	m[0] = cosf(ar);  m[1] = sinf(ar);
	m[4] = -m[1];     m[5] = m[0];
}

void GLMatrix4x4::matrixMultyply(GLfloat* m1, GLfloat* m2, GLfloat* r){

	r[0]  = m1[0]*m2[0]  + m1[4]*m2[1]  + m1[8] *m2[2]  + m1[12]*m2[3];
	r[1]  = m1[1]*m2[0]  + m1[5]*m2[1]  + m1[9] *m2[2]  + m1[13]*m2[3];
	r[2]  = m1[2]*m2[0]  + m1[6]*m2[1]  + m1[10]*m2[2]  + m1[14]*m2[3];
	r[3]  = m1[3]*m2[0]  + m1[7]*m2[1]  + m1[11]*m2[2]  + m1[15]*m2[3];

	r[4]  = m1[0]*m2[4]  + m1[4]*m2[5]  + m1[8] *m2[6]  + m1[12]*m2[7];
	r[5]  = m1[1]*m2[4]  + m1[5]*m2[5]  + m1[9] *m2[6]  + m1[13]*m2[7];
	r[6]  = m1[2]*m2[4]  + m1[6]*m2[5]  + m1[10]*m2[6]  + m1[14]*m2[7];
	r[7]  = m1[3]*m2[4]  + m1[7]*m2[5]  + m1[11]*m2[6]  + m1[15]*m2[7];

	r[8]  = m1[0]*m2[8]  + m1[4]*m2[9]  + m1[8] *m2[10] + m1[12]*m2[11];
	r[9]  = m1[1]*m2[8]  + m1[5]*m2[9]  + m1[9] *m2[10] + m1[13]*m2[11];
	r[10] = m1[2]*m2[8]  + m1[6]*m2[9]  + m1[10]*m2[10] + m1[14]*m2[11];
	r[11] = m1[3]*m2[8]  + m1[7]*m2[9]  + m1[11]*m2[10] + m1[15]*m2[11];

	r[12] = m1[0]*m2[12] + m1[4]*m2[13] + m1[8] *m2[14] + m1[12]*m2[15];
	r[13] = m1[1]*m2[12] + m1[5]*m2[13] + m1[9] *m2[14] + m1[13]*m2[15];
	r[14] = m1[2]*m2[12] + m1[6]*m2[13] + m1[10]*m2[14] + m1[14]*m2[15];
	r[15] = m1[3]*m2[12] + m1[7]*m2[13] + m1[11]*m2[14] + m1[15]*m2[15];
}

void GLMatrix4x4::matrixOrtho( GLfloat* m, GLfloat left, GLfloat right,
			GLfloat top, GLfloat bottom, GLfloat near, GLfloat far ){

	m[0] = 2.0 / (right - left); m[1] = 0.f; m[2] = 0.f; m[3] = 0.f;
	m[4] = 0.f; m[5] = 2.f / (top - bottom); m[6] = 0.f; m[7] = 0.f;
	m[8] = 0.f; m[9] = 0.f; m[10] = -2.0 / (far - near); m[11] = 0.f;

	m[12] = - (right + left) / (right - left);
	m[13] = - (top + bottom) / (top - bottom);
	m[14] = - (far + near) / (far - near);
	m [15] = 1.f;
}

void GLMatrix4x4::matrixProjection( GLfloat* m, GLfloat near, GLfloat far,
			GLfloat angleOfView, GLfloat aspectRatio ){

	GLfloat size = near * tanf(angleOfView / 2.0);
	GLfloat left   = -size;
	GLfloat right  = size;
	GLfloat bottom = -size / aspectRatio;
	GLfloat top    =  size / aspectRatio;

	m[0] = 2 * near / (right - left); m[1] = 0.f, m[2] = 0.f; m[3] = 0.f;
	m[4] = 0.f; m[5] = 2 * near / (top - bottom); m[6] = 0.f; m[7] = 0.f;

	m[8] = (right + left)/(right - left);
	m[9] = (top + bottom)/(top - bottom);
	m[10] = -(far + near)/(far - near);
	m[11] = -1.f;

	m[12] = 0.f; m[13] = 0.f; m[14] = -(2 * far * near)/(far - near); m[15] = 0.f;
}

























