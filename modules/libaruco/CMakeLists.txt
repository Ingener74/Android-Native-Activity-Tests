cmake_minimum_required(VERSION 2.8) 

set(PROJECT_NAME aruco)
project(${PROJECT_NAME})

include_directories(
	${ANDROID_NDK}/platforms/android-14/arch-arm/usr/include
	${ANDROID_NDK}/sources/android/native_app_glue
	${ANDROID_NDK}/toolchains/arm-linux-androideabi-4.7/prebuilt/linux-x86/include
	${REPO_HOME}/3rdparty/OpenCV-2.4.4-android-sdk/sdk/native/jni/include
	${REPO_HOME}/modules/libtools/include
	)
	
link_directories(
    ${REPO_HOME}/3rdparty/OpenCV-2.4.4-android-sdk/sdk/native/libs/armeabi-v7a
    )
	
set(SOURCES 
  src/arucofidmarkers.cpp
  src/board.cpp
  src/boarddetector.cpp
  src/cameraparameters.cpp
  src/cvdrawingutils.cpp
  src/marker.cpp
  src/markerdetector.cpp
  )
  
set(LIBS
  z
  )
set(OPENCV_LIBS 
  opencv_core
  opencv_highgui
  opencv_androidcamera
  opencv_imgproc
  opencv_features2d
  opencv_calib3d
  opencv_flann
  opencv_legacy
  
  IlmImf
  libjasper
  libjpeg
  libpng
  libtiff
  tbb  
  )
  
add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBS} ${OPENCV_LIBS})
