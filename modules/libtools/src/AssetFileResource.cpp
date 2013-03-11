/*
 * AssetFileResource.cpp
 *
 *  Created on: 27.02.2013
 *      Author: pavel
 */

#include "AssetFileResource.h"

AssetFileResource::AssetFileResource(): _desc(-1), _start(0),
	_length(0){
}

AssetFileResource::~AssetFileResource() {
}

bool AssetFileResource::open( android_app* application, const char* path ){
	LOGI("AssetFileResource::open", "begin");
	AAsset* _asset = AAssetManager_open(application->activity->assetManager, path, AASSET_MODE_UNKNOWN);
	if(_asset){
		_desc = AAsset_openFileDescriptor(_asset, &_start, &_length);
		LOGI("AssetFileResource::open", "desc = %d, start = %d, len = %d", _desc, _start, _length);
		AAsset_close(_asset);
		return true;
	}else{
		LOGE("AssetFileResource::open", "error: asset not opened");
		return false;
	}
}

