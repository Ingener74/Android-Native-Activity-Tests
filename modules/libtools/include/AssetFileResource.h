/*
 * AssetFileResource.h
 *
 *  Created on: 27.02.2013
 *      Author: pavel
 */

#ifndef ASSETFILERESOURCE_H_
#define ASSETFILERESOURCE_H_

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android_native_app_glue.h>

#include "tools.h"

class AssetFileResource {
public:
	AssetFileResource();
	virtual ~AssetFileResource();

	bool open( android_app* application, const char* path );

	int32_t _desc;
	off_t   _start;
	off_t   _length;
};

#endif /* ASSETFILERESOURCE_H_ */
