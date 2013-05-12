cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME tools)
project(${PROJECT_NAME})

include_directories(
    include
    ${CMAKE_INSTALL_PREFIX}/3rdparty/sdk/native/jni/include
	${ANDROID_NDK}/sources/android/native_app_glue
	${ANDROID_NDK}/platforms/android-14/arch-arm/usr/include
)

link_directories(
)

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
    
    tbb
    libpng
    libjpeg
    libtiff
    libjasper
    IlmImf
    )

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${OPENCV_LIBS})
