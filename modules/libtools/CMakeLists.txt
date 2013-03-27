cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME tools)
project(${PROJECT_NAME})

include_directories(
	${ANAT_INCLUDE}
	include
	)
	
link_directories(${REPO_HOME}/3rdparty/OpenCV-2.4.4-android-sdk/sdk/native/libs/armeabi-v7a)

file(GLOB SOURCES src/*.cpp)

set(OPENCV_LIBS   
    opencv_highgui   
    opencv_androidcamera   
    opencv_imgproc   
    opencv_core
    tbb
    libpng
    libjpeg
    libtiff
    libjasper
    IlmImf
    )

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${OPENCV_LIBS})
