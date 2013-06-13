cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME tools)
project(${PROJECT_NAME})

include_directories(
	include
	${INSTALL_3RDPARTY}/include
	)
if(ANDROID)
        include_directories(
		${INSTALL_3RDPARTY}/sdk/native/jni/include
		${ANDROID_NDK}/sources/android/native_app_glue
	        ${ANDROID_NDK}/platforms/android-14/arch-arm/usr/include
		)
        link_directories(${INSTALL_3RDPARTY}/sdk/native/libs/armeabi-v7a)
        link_directories(${INSTALL_3RDPARTY}/sdk/native/3rdparty/libs/armeabi-v7a)
endif(ANDROID)

file(GLOB SOURCES src/*.cpp)

set(OPENCV_LIBS
    opencv_highgui
    opencv_androidcamera
    opencv_imgproc
    opencv_core
    
    opencv_calib3d
    opencv_objdetect
    opencv_features2d
    opencv_flann
    opencv_java
    
    #tbb
    libpng
    libjpeg
    libtiff
    libjasper
    IlmImf
    )

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${OPENCV_LIBS})
