/*
 * IMeshExporter.h
 *
 *  Created on: 31.03.2013
 *      Author: ingener
 */

#ifndef IMESHEXPORTER_H_
#define IMESHEXPORTER_H_

#include <stdint.h>

#ifdef ANDROID
	#include <GLES2/gl2.h>
#else
	#include <GL/gl.h>
#endif

#include <ErrorHandler.h>

class IMeshExporter: public ErrorHandler {
public:
	IMeshExporter();
	virtual ~IMeshExporter();

	virtual uint32_t getNumOfVertexes() = 0;
	virtual GLfloat* getVertexes()      = 0;

	virtual uint32_t getNumOfUVs()      = 0;
	virtual GLfloat* getUVs()           = 0;

	virtual uint32_t getNumOfNormals()  = 0;
	virtual GLfloat* getNormals()       = 0;
};

#endif /* IMESHEXPORTER_H_ */
