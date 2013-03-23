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

//#include "GLTriangle.h"

#ifdef BUILD_ANDROID
	#include <GLES2/gl2.h>
#else
	#include <GL/gl.h>
#endif

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
	MeshV( const LoadedObject& lo ){

		const vector<Vertex>& vertexes = lo.getVertexes();
		const vector<vector<Face> >& faces = lo.getFaces();

		_vertexes = new GLfloat[ vertexes.size() * 3 ];
		if(_vertexes){
			for( uint32_t i = 0; i < vertexes.size(); ++i ){
				_vertexes[3*i + 0] = vertexes[i].x;
				_vertexes[3*i + 1] = vertexes[i].y;
				_vertexes[3*i + 2] = vertexes[i].z;
			}

			_indexes = new GLushort[ faces.size() * 3 ];
			if( _indexes ){

//				for( uint32_t i = 0; i )
			}
		}
	}

	GLfloat* getVertexes() { return _vertexes; }
	GLushort* getIndexes() { return _indexes;  }

	virtual ~MeshV(){
		delete [] _vertexes;
		delete [] _indexes;
	}
private:
	GLfloat*  _vertexes;
	GLushort* _indexes;
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
