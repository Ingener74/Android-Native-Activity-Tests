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

//		vector<Vertex>         vertexes;
//		vector<TextureCoordinate>  texcoords;
//		vector<Normal>         normals;
//		vector<vector<Face> >  faces;

		LoadedObject lo;

		ifstream file(filename);
		if(file.is_open()){

			string t;
			while(file >> t){

				cout << t << endl;

				if( !t.compare("v") ){
					Vertex v;
					file >> v.x >> v.y >> v.z;
					lo.addVertex(v);
				}
				if( !t.compare("vt") ){
					TextureCoordinate vt;
					file >> vt.u >> vt.v >> vt.w;
					lo.addTextureCoord(vt);
				}
				if( !t.compare("vn")){
					Normal vn;
					file >> vn.x >> vn.y >> vn.z;
					lo.addNormal(vn);
				}

				if( !t.compare("f") ){
					vector<Face> faces;
					string s;
					file >> s;
					while( (s.compare("f") && s.compare("s")) ){

						Face f;

						vector<string> x = split(s, '/');
						for( uint32_t i = 0; i < x.size(); ++i ){
							stringstream ss;
							ss << x[i];
							ss >> f.f[i];
						}

						faces.push_back(f);

						file >> s;
					}

					lo.addFace(faces);

					cout << "object loaded" << endl;
				}

				if( !t.compare("o") ){
					cout << "new object" << endl;
				}
				if( !t.compare("g") ){
					cout << "new group" << endl;
				}
			}

			_objects.push_back(lo);

			cout << "file loaded" << endl;

		}else{
			cerr << "file not opened" << endl;
		}
	}else{
		cerr << "filename is null" << endl;
	}
}

OBJLoader::~OBJLoader() {
}


















