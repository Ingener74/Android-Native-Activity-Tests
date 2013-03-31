/*
 * Mesh.h
 *
 *  Created on: 17.03.2013
 *      Author: pavel
 */

#ifndef MESH_H_
#define MESH_H_

//#ifdef ANDROID
#include <GLES/gl.h>
#include <GLES2/gl2.h>
//#else
//#include <GL/gl.h>
//#endif

#include <IObject.h>
#include <IMeshExporter.h>
#include <ITexture.h>

class Mesh: public IObject {
public:
	Mesh( IMeshExporter* me , GLuint shaderVertexAttribute, ITexture* tex = NULL,
			GLuint shaderUVAttribute = -1, GLuint shaderNormalAttribute = -1 );

	virtual ~Mesh();

	virtual void draw();

private:
	ITexture*      _tex;

	GLuint _shaderVertexAttribute;
	GLuint _shaderUVAttribute;
	GLuint _shaderNormalAttribute;

	GLuint _vVBO;
	GLuint _vtVBO;
	GLuint _vnVBO;

	uint32_t _n;
};

#endif /* MESH_H_ */
