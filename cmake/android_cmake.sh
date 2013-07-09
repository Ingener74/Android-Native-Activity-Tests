#!/bin/sh

if [ -z $1 ]; then
	echo "Usage: cd <repo>"
	echo "       mkdir build_android && cd build_android && ../cmake/android_cmake.sh <android-cmake-toolchain-file>"
else
	cmake .. -DCMAKE_TOOLCHAIN_FILE=$1 -DANDROID_NATIVE_API_LEVEL=14 -DCMAKE_BUILD_TYPE=Release -DEXECUTABLE_OUTPUT_PATH=$PWD/bin -DLIBRARY_OUTPUT_PATH=$PWD/libs/armeabi-v7a -DLIBRARY_OUTPUT_PATH_ROOT=$PWD
fi
