cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME aruco)
project(${PROJECT_NAME})

include_directories(${INSTALL_3RDPARTY}/include)
if(ANDROID)
	include_directories(${INSTALL_3RDPARTY}/sdk/native/jni/include)
	link_directories(${INSTALL_3RDPARTY}/sdk/native/libs/armeabi-v7a)
	link_directories(${INSTALL_3RDPARTY}/sdk/native/3rdparty/libs/armeabi-v7a)
endif(ANDROID)

file(GLOB SOURCES src/*.cpp)

set(OPENCV_LIBS opencv_core opencv_highgui opencv_imgproc opencv_calib3d opencv_objdetect opencv_features2d opencv_flann)

if(ANDROID)
	set(ANDROID_LIBS 
		z 
		opencv_androidcamera 
		opencv_java 
		IlmImf 
		libjasper 
		libjpeg 
		libpng 
		libtiff 
		#tbb
		)
else(ANDROID)
endif(ANDROID)

add_library(${PROJECT_NAME} ${SOURCES})
if(ANDROID)
	target_link_libraries(${PROJECT_NAME} ${OPENCV_LIBS} ${ANDROID_LIBS})
else(ANDROID)
	target_link_libraries(${PROJECT_NAME} ${OPENCV_LIBS})
endif(ANDROID)

