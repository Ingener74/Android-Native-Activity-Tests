/*
 * OBJLoader.cpp
 *
 *  Created on: 16.03.2013
 *      Author: pavel
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "../include/OBJLoader.h"

struct vertex{
	vertex( float x = 0, float y = 0, float z = 0 ): x(x), y(y), z(z){}
	float x, y, z;
};
struct texture_coord{
	texture_coord( float x = 0, float y = 0, float z = 0): x(x), y(y), z(z){}
	float x, y, z;
};
struct normal{
	normal( float x = 0, float y = 0, float z = 0 ): x(x), y(y), z(z){}
	float x, y, z;
};
struct face{
	face( uint16_t v = 0, uint16_t vt = 0, uint16_t vn = 0):
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

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}

OBJLoader::OBJLoader( const char* filename ) {

	if(filename){

		vector<vertex>         vertexes;
		vector<texture_coord>  texcoords;
		vector<normal>         normals;
		vector<vector<face> >  faces;

		ifstream file(filename);
		if(file.is_open()){

			string t;
			while(file >> t){

				cout << t << endl;

				if( !t.compare("v") ){
					vertex v;
					file >> v.x >> v.y >> v.z;
					vertexes.push_back(v);
				}
				if( !t.compare("vt") ){
					texture_coord vt;
					file >> vt.x >> vt.y >> vt.z;
					texcoords.push_back(vt);
				}
				if( !t.compare("vn")){
					normal vn;

					file >> vn.x >> vn.y >> vn.z;
					normals.push_back(vn);
				}

				if( !t.compare("f") ){

					vector<face> faces;

					string s;
					file >> s;
					while( (s.compare("f") && s.compare("s")) ){

						cout << s << endl;

						face f;

						vector<string> x = split(s, '/');
						for( uint32_t i = 0; i < x.size(); ++i ){
							stringstream ss;
							ss << x[i];
							ss >> f.f[i];
						}

						faces.push_back(f);

						file >> s;
					}

				}

				if( !t.compare("o") ){
					cout << "new object" << endl;
				}
				if( !t.compare("g") ){
					cout << "new group" << endl;
				}
			}

		}else{
			cerr << "file not opened" << endl;
		}
	}else{
		cerr << "filename is null" << endl;
	}
}

OBJLoader::~OBJLoader() {
}

