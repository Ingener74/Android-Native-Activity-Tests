/*
 * RAWMeshExporter.cpp
 *
 *  Created on: 31.03.2013
 *      Author: ingener
 */

#include "RAWMeshExporter.h"

RAWMeshExporter::RAWMeshExporter( uint32_t n, GLfloat* vertexs, GLfloat* uvs,
		GLfloat* normals): _n(n), _vertexs(vertexs), _uvs(uvs),
		_normals(normals) {
}

RAWMeshExporter::~RAWMeshExporter() {
}

uint32_t RAWMeshExporter::getNumOfVertexes(){ return _n; }
GLfloat* RAWMeshExporter::getVertexes(){ return _vertexs; }

uint32_t RAWMeshExporter::getNumOfUVs(){ return _n; }
GLfloat* RAWMeshExporter::getUVs(){ return _uvs; }

uint32_t RAWMeshExporter::getNumOfNormals(){ return _n; }
GLfloat* RAWMeshExporter::getNormals(){ return _normals; }
