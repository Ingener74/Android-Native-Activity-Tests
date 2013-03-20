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
	
#include_directories(/home/ingener/prj/Android-Native-Activity-Tests/3rdparty/OpenCV-2.4.4-android-sdk/sdk/native/jni/include)
#include_directories(/home/ingener/android_dev/android-ndk-r8d/platforms/android-14/arch-arm/usr/include)
#include_directories(/home/ingener/android_dev/android-ndk-r8d/sources/android/native_app_glue)
#include_directories(/home/ingener/android_dev/android-ndk-r8d/toolchains/arm-linux-androideabi-4.7/prebuilt/linux-x86/lib/gcc/arm-linux-androideabi/4.7/include)
#link_directories(/home/ingener/prj/Android-Native-Activity-Tests/3rdparty/OpenCV-2.4.4-android-sdk/sdk/native/3rdparty/libs/armeabi-v7a)
#link_directories(/home/ingener/prj/Android-Native-Activity-Tests/3rdparty/OpenCV-2.4.4-android-sdk/sdk/native/libs/armeabi-v7a)
#link_directories(/home/ingener/android_dev/android-ndk-r8d/platforms/android-14/arch-arm/usr/lib)

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
  opencv_imgproc
  
  IlmImf
  libjasper
  libjpeg
  libpng
  libtiff
  tbb  
  )
  
add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBS} ${OPENCV_LIBS})