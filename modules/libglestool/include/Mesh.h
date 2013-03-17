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
#include "IShaderProgram.h"

struct MeshVertex{
	GLfloat x, y, z;
//	GLfloat nx, ny, nz;
//	GLfloat s, t;
};

class Mesh: public IObject {
public:
	Mesh( const MeshVertex* vertices,
			GLuint numOfVertex,
			const char* vertexAttr,
			const GLuint* faces,
			GLuint numOfFaces,
			IShaderProgram* shaderProgram );

	virtual ~Mesh();

	virtual void draw();

private:
	GLuint _vertex;
	GLuint _faces;

	GLuint _vertAttr;

	IShaderProgram* _shaderProgram;
};

#endif /* MESH_H_ */
