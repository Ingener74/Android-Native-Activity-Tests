/*
 * IShaderLoader.h
 *
 *  Created on: 31.03.2013
 *      Author: ingener
 */

#ifndef ISHADERLOADER_H_
#define ISHADERLOADER_H_

#include "ErrorHandler.h"

class IShaderLoader: public ErrorHandler {
public:
	IShaderLoader();
	virtual ~IShaderLoader();

	virtual char* getVertexSource()   = 0;
	virtual char* getFragmentSource() = 0;
};

#endif /* ISHADERLOADER_H_ */
