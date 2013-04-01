/*
 * FileShaderLoader.h
 *
 *  Created on: 31.03.2013
 *      Author: ingener
 */

#ifndef FILESHADERLOADER_H_
#define FILESHADERLOADER_H_

#include <stdint.h>
#include <fstream>

#include <tools.h>
#include "IShaderLoader.h"

using namespace std;

class FileShaderLoader: public IShaderLoader {
public:
	FileShaderLoader(
			const char* vertexShaderFile,
			const char* fragmentShaderFile );
	virtual ~FileShaderLoader();

	char* getVertexSource();
	char* getFragmentSource();

private:
	const static uint32_t maxFileSize = 1024 * 10;
	char vertexSource[maxFileSize];
	char fragmentSource[maxFileSize];
};

#endif /* FILESHADERLOADER_H_ */
