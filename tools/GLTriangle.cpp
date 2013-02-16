/*
 * GLTriangle.cpp
 *
 *  Created on: 16.02.2013
 *      Author: pavel
 */

#include "GLTriangle.h"

GLTriangle::~GLTriangle() {
}

GLTriangle::GLTriangle(ITexture* tex, GLfloat* vertexes, GLfloat* texcoords,
		GLfloat* colors, GLushort* indexes, int32_t elements) :
		_tex(tex), _vertexs(vertexes), _texcoords(texcoords), _colors(colors), _indexes(
				indexes), _elements(elements) {
}

void GLTriangle::setTexture(ITexture* tex) {
	_tex = tex;
}

void GLTriangle::draw() {
	if (_tex)
		_tex->bind();

	LOGI("GLTriangle draw begin");

	glEnableClientState(GL_VERTEX_ARRAY);
	GLERR
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	GLERR
	glEnableClientState(GL_COLOR_ARRAY);
	GLERR

	glVertexPointer(3, GL_FLOAT, 0, _vertexs);
	GLERR
	glTexCoordPointer(2, GL_FLOAT, 0, _texcoords);
	GLERR
	glColorPointer(4, GL_FLOAT, 0, _colors);
	GLERR

	glFrontFace(GL_CCW);

	glDrawElements(GL_TRIANGLES, _elements, GL_UNSIGNED_SHORT, _indexes);
	GLERR

	glDisableClientState(GL_VERTEX_ARRAY);
	GLERR
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	GLERR
	glDisableClientState(GL_COLOR_ARRAY);
	GLERR

	LOGI("GLTriangle draw end");
}
