#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>

#include <glm/glm.hpp>

#include "IMeshExporter.h"

using namespace std;
using namespace glm;

class extOBJLoader: public IMeshExporter{
public:
	extOBJLoader( const char* fileName);

	uint32_t getNumOfVertexes();
	GLfloat* getVertexes();

	uint32_t getNumOfUVs();
	GLfloat* getUVs();

	uint32_t getNumOfNormals();
	GLfloat* getNormals();

private:
	bool load( const char* fileName );

	vector<vec3> _v;
	vector<vec2> _vt;
	vector<vec3> _vn;
};

#endif
