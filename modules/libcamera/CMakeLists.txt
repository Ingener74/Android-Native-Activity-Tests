cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME camera)
project(${PROJECT_NAME})

set(SOURCES 
	src/capture.c
	src/capture.h
	src/util.c
	src/util.h
	src/video_device.c
	src/video_device.h
	#src/webcam.c
	#src/webcam.h
	src/yuv.c
	src/yuv.h
	)
	
link_directories(
    ${ANDROID_NDK}/platforms/android-14/arch-arm/usr/lib
    )

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} log)