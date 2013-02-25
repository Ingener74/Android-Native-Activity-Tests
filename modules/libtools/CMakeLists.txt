cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME tools)
project(${PROJECT_NAME})

include_directories(
	${ANDROID_NDK}/platforms/android-14/arch-arm/usr/include
	${ANDROID_NDK}/sources/android/native_app_glue
	${ANDROID_NDK}/toolchains/arm-linux-androideabi-4.7/prebuilt/linux-x86/include
	${REPO_HOME}/3rdparty/OpenCV-2.4.4-android-sdk/sdk/native/jni/include
	${REPO_HOME}/modules/libtools/include
	)

set(SOURCES 
	src/IEventEngine.cpp
	src/IGraphicsService.cpp
	src/ICaptureService.cpp
	src/NullCapture.cpp
	src/OpenCVCapture.cpp
	src/IObject.cpp
	src/GLTriangle.cpp
	src/ITexture.cpp
	src/RGBTexture.cpp
	)
	
set(OPENCV_LIBS
    opencv_core
    opencv_highgui
    opencv_imgproc
    )

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${OPENCV_LIBS})