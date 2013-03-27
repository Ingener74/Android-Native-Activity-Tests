cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME aruco)
project(${PROJECT_NAME})

include_directories(${ANAT_INCLUDE})
link_directories(${ANAT_LINK})

file(GLOB SOURCES src/*.cpp)

set(ANDROID_LIBS z)

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
target_link_libraries(${PROJECT_NAME} ${ANDROID_LIBS} ${OPENCV_LIBS})
