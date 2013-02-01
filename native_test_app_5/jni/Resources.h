/*
 * Resources.h
 *
 *  Created on: 27.01.2013
 *      Author: pavel
 */

#ifndef RESOURCES_H_
#define RESOURCES_H_

#include <android_native_app_glue.h>

#include "Types.hpp"

namespace smallarsdk {

class Resources {
public:
	Resources( android_app* application, const char* path );

	const char* getPath() const ;

	status open();
	void close();
	status read( void* buffer, size_t count );

private:
	const char*     _path;
	AAssetManager*  _assetManager;
	AAsset*         _asset;
};

} /* namespace smallarsdk */
#endif /* RESOURCES_H_ */
