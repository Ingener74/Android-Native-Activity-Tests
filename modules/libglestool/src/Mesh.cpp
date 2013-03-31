/*
 * Mesh.cpp
 *
 *  Created on: 17.03.2013
 *      Author: pavel
 */

#include "Mesh.h"

Mesh::Mesh( IMeshExporter* me, GLuint shaderVertexAttribute, ITexture* tex,
		GLuint shaderUVAttribute, GLuint shaderNormalAttribute):
		_tex(tex),
		_shaderVertexAttribute(shaderVertexAttribute),
		_shaderUVAttribute(shaderUVAttribute),
		_shaderNormalAttribute(shaderNormalAttribute),

		_vVBO(0),
		_vtVBO(0),
		_vnVBO(0)
	{

	glGenBuffers(1, &_vVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _vVBO);
	glBufferData(GL_ARRAY_BUFFER, me->getNumOfVertexes() * 3 * sizeof(GLfloat), (GLvoid*)me->getVertexes(), GL_STATIC_DRAW);

	_n = me->getNumOfVertexes();

	if(shaderUVAttribute != -1){
		glGenBuffers(1, &_vtVBO);
		glBindBuffer(GL_ARRAY_BUFFER, _vtVBO);
		glBufferData(GL_ARRAY_BUFFER, me->getNumOfUVs() * 2 * sizeof(GLfloat), (GLvoid*)me->getUVs(), GL_STATIC_DRAW);
	}
	if(shaderNormalAttribute != -1){
		glGenBuffers(1, &_vnVBO);
		glBindBuffer(GL_ARRAY_BUFFER, _vnVBO);
		glBufferData(GL_ARRAY_BUFFER, me->getNumOfNormals() * 3 * sizeof(GLfloat), (GLvoid*)me->getNormals(), GL_STATIC_DRAW);
	}
}

Mesh::~Mesh() {
	glDeleteBuffers(1, &_vVBO);
	glDeleteBuffers(1, &_vtVBO);
	glDeleteBuffers(1, &_vnVBO);
}

void Mesh::draw(){

	if(_tex){
		_tex->bind();
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vVBO);
	glVertexAttribPointer(_shaderVertexAttribute, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(_shaderVertexAttribute);

	if(_shaderUVAttribute != -1){
		glBindBuffer(GL_ARRAY_BUFFER, _vtVBO);
		glVertexAttribPointer(_shaderUVAttribute, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(_shaderUVAttribute);
	}

	if(_shaderNormalAttribute != -1){
		glBindBuffer(GL_ARRAY_BUFFER, _vtVBO);
		glVertexAttribPointer(_shaderNormalAttribute, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(_shaderNormalAttribute);
	}

	glDrawArrays(GL_TRIANGLES, 0, _n );

	glDisableVertexAttribArray(_shaderVertexAttribute);
	if(_shaderUVAttribute != -1)
		glDisableVertexAttribArray(_shaderUVAttribute);
	if(_shaderNormalAttribute != -1)
		glDisableVertexAttribArray(_shaderNormalAttribute);

}
