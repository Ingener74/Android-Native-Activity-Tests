/*
 * RAWMeshExporter.h
 *
 *  Created on: 31.03.2013
 *      Author: ingener
 */

#ifndef RAWMESHEXPORTER_H_
#define RAWMESHEXPORTER_H_

#include "IMeshExporter.h"

class RAWMeshExporter: public IMeshExporter {
public:
	RAWMeshExporter( uint32_t n, GLfloat* vertexs, GLfloat* uvs = NULL, GLfloat* normals = NULL );
	virtual ~RAWMeshExporter();

	uint32_t getNumOfVertexes();
	GLfloat* getVertexes();

	uint32_t getNumOfUVs();
	GLfloat* getUVs();

	uint32_t getNumOfNormals();
	GLfloat* getNormals();

public:
	uint32_t _n;

	GLfloat* _vertexs;
	GLfloat* _uvs;
	GLfloat* _normals;
};

#endif /* RAWMESHEXPORTER_H_ */
