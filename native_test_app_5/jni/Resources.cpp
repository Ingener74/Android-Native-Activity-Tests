/*
 * Resources.cpp
 *
 *  Created on: 27.01.2013
 *      Author: pavel
 */

#include "Resources.h"

namespace smallarsdk {

Resources::Resources( android_app* application, const char* path ):
	_path(path),
	_assetManager(application->activity->assetManager),
	_asset(NULL){
}

const char* Resources::getPath() const {
	return _path;
}

status Resources::open(){
	_asset = AAssetManager_open(_assetManager, _path, AASSET_MODE_UNKNOWN);
	return (_asset != NULL)? STATUS_OK : STATUS_KO;
}

void Resources::close(){
	if(_asset != NULL){
		AAsset_close(_asset);
		_asset = NULL;
	}
}

status Resources::read( void** buffer, size_t count ){
	int32_t readCount = AAsset_read(_asset, buffer, count );
	return (readCount == count) ? STATUS_OK : STATUS_KO;
}

} /* namespace smallarsdk */
