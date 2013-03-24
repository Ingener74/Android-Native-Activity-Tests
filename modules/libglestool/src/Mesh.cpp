/*
 * Mesh.cpp
 *
 *  Created on: 17.03.2013
 *      Author: pavel
 */

#include "Mesh.h"

Mesh::Mesh( const MeshV& mv, GLuint shaderVertexAttribute ):
	_shaderVertexAttribute(shaderVertexAttribute),
	_vertexVBO(0),
	_indexVBO(0),
	_numOfFaces(0){

	glGenBuffers(1, &_vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, mv.getNumOfVertexes() * 3 * sizeof(GLfloat), (GLvoid*)mv.getVertexes(), GL_STATIC_DRAW);

	glGenBuffers(1, &_indexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mv.getNumOfIndexes() * sizeof(GLfloat), (GLvoid*)mv.getIndexes(), GL_STATIC_DRAW);

	_numOfFaces = mv.getNumOfIndexes();
}

Mesh::~Mesh() {
}

void Mesh::draw(){

	glBindBuffer(GL_ARRAY_BUFFER, _vertexVBO);
	glVertexAttribPointer(_shaderVertexAttribute, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(_shaderVertexAttribute);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexVBO);
	glDrawElements(GL_TRIANGLES, _numOfFaces, GL_UNSIGNED_SHORT, (GLvoid*)0);

	glDisableVertexAttribArray(_shaderVertexAttribute);

}
