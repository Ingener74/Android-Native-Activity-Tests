/*
 * Mesh.cpp
 *
 *  Created on: 17.03.2013
 *      Author: pavel
 */

#include "Mesh.h"

Mesh::Mesh( const MeshVertex* vertices,
		GLuint numOfVertex,
		const char* vertexAttr,
		const GLuint* faces,
		GLuint numOfFaces,
		IShaderProgram* shaderProgram ):

		_vertex(0), _faces(0), _shaderProgram(shaderProgram){

	glGenBuffers(1, &_vertex);
	glBindBuffer(GL_ARRAY_BUFFER, _vertex);
	glBufferData(GL_ARRAY_BUFFER, numOfVertex * sizeof(MeshVertex),
			(GLvoid*)vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &_faces);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _faces);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)* numOfFaces,
			(GLvoid*)faces, GL_STATIC_DRAW);

	_vertAttr = _shaderProgram->getAttribute(vertexAttr);
}

Mesh::~Mesh() {
}

void Mesh::draw(){

	_shaderProgram->useProgram();

	glBindBuffer(GL_ARRAY_BUFFER, _vertex);

	glEnableVertexAttribArray(_vertAttr);

	glVertexAttribPointer(_vertAttr, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (GLvoid*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _faces);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (GLvoid*)0);

	glDisableVertexAttribArray(_vertAttr);
}
