/*
 * OBJLoader.h
 *
 *  Created on: 16.03.2013
 *      Author: pavel
 */

#ifndef OBJLOADER_H_
#define OBJLOADER_H_

#include <stdint.h>
#include <stdlib.h>

#include <vector>


#include <GLES2/gl2.h>
//#include <GL/gl.h>

using namespace std;

struct Vertex{
	Vertex( float x = 0, float y = 0, float z = 0 ): x(x), y(y), z(z){}
	float x, y, z;
};
struct TextureCoordinate{
	TextureCoordinate( float x = 0, float y = 0, float z = 0): u(x), v(y), w(z){}
	float u, v, w;
};
struct Normal{
	Normal( float x = 0, float y = 0, float z = 0 ): x(x), y(y), z(z){}
	float x, y, z;
};
struct Face{
	Face( uint16_t v = 0, uint16_t vt = 0, uint16_t vn = 0):
		v(v), vt(vt), vn(vn){}
	union{
		uint16_t f[3];
		struct{
			uint16_t v;
			uint16_t vt;
			uint16_t vn;
		};
	};
};


class LoadedObject{
public:
	LoadedObject(){
	}
	virtual ~LoadedObject(){}
	void addVertex( const Vertex& v ){
		_vertexes.push_back(v);
	}
	void addTextureCoord( const TextureCoordinate& vt ){
		_texcoords.push_back(vt);
	}
	void addNormal( const Normal& vn ){
		_normals.push_back(vn);
	}
	void addFace( const vector<Face>& f ){
		_faces.push_back(f);
	}

	const vector<Vertex>& getVertexes() const { return _vertexes; }
	const vector<vector<Face> >& getFaces() const { return _faces; }

private:
	vector<Vertex>             _vertexes;
	vector<TextureCoordinate>  _texcoords;
	vector<Normal>             _normals;
	vector<vector<Face> >      _faces;
};

struct MeshV{
	MeshV():
		_vertexes(NULL), _numOfVertexes(0),
		_indexes(NULL), _numOfIndexes(0){
	}
	virtual ~MeshV(){
		delete [] _vertexes;
		delete [] _indexes;
	}

	bool createMesh( const LoadedObject& lo );

	const GLfloat*  getVertexes() const { return _vertexes; }
	const GLushort* getIndexes()  const { return _indexes;  }

	GLuint    getNumOfVertexes() const { return _numOfVertexes; }
	GLuint    getNumOfIndexes()  const { return _numOfIndexes;  }

private:
	GLfloat*  _vertexes; GLuint _numOfVertexes;
	GLushort* _indexes;  GLuint _numOfIndexes;
};

class OBJLoader {
public:
	OBJLoader( const char* filename = NULL );
	virtual ~OBJLoader();

	uint32_t getNumOfLoadedObjects(){ return _objects.size(); }
	const LoadedObject& getObject( uint32_t i ){ return _objects[i]; }
private:
	vector<LoadedObject> _objects;
};

#endif /* OBJLOADER_H_ */
