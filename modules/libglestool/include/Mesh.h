/*
 * Mesh.h
 *
 *  Created on: 17.03.2013
 *      Author: pavel
 */

#ifndef MESH_H_
#define MESH_H_

#include <GLES/gl.h>
#include <GLES2/gl2.h>

#include <IObject.h>
#include "OBJLoader.h"

class Mesh: public IObject {
public:
	Mesh( const MeshV& mv, GLuint shaderVertexAttribute );

	virtual ~Mesh();

	virtual void draw();

private:

	GLuint _shaderVertexAttribute;

	GLuint _vertexVBO;
	GLuint _indexVBO;

	uint32_t _numOfFaces;

};

#endif /* MESH_H_ */
