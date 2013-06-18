cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME camera)
project(${PROJECT_NAME})

include_directories(
    include
    )

set(SOURCES 
	src/capture.cpp
	src/util.cpp
	src/video_device.cpp
	src/yuv.cpp
	)
	
link_directories(
    ${ANDROID_NDK}/platforms/android-14/arch-arm/usr/lib
    )

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} log)