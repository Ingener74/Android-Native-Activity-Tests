/*
 * GLTriangle.h
 *
 *  Created on: 16.02.2013
 *      Author: pavel
 */

#ifndef GLTRIANGLE_H_
#define GLTRIANGLE_H_

#include <GLES/gl.h>

#include "GLObject.h"
#include "ITexture.h"
#include "HTATools.h"

class GLTriangle: public GLObject {
public:
	virtual ~GLTriangle();
	GLTriangle(ITexture* tex, GLfloat* vertexes, GLfloat* texcoords,
			GLfloat* colors, GLushort* indexes, int32_t elements);

	void setTexture( ITexture* tex );

	virtual void draw();

private:
	ITexture* _tex;
	GLfloat*  _vertexs;
	GLfloat*  _texcoords;
	GLfloat*  _colors;
	GLushort* _indexes;
	int32_t   _elements;
};

#endif /* GLTRIANGLE_H_ */
