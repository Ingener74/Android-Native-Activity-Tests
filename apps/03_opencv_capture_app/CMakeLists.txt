cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME 03_opencv_capture_app)
project(${PROJECT_NAME})

include_directories(
    ${ANAT_INCLUDE}
    ../../modules/libtools/include
    ../../modules/libglestool/include
    ../../modules/libaruco/include
    )
link_directories( ${ANAT_LINK} )
set(ANDROID_LIBS 
    log 
    android 
    EGL 
    GLESv1_CM
    GLESv2
    OpenSLES
    OpenMAXAL
    z        
    )
set(OPENCV_LIBS 
    opencv_highgui
    opencv_imgproc
    opencv_androidcamera
    opencv_core    
    opencv_features2d
    opencv_calib3d
    opencv_flann
    opencv_legacy
    
    tbb
    libpng
    libjpeg
    libtiff
    libjasper
    IlmImf
    )
    
file(GLOB SRC src/*.cpp)
set(SOURCES  ${ANAT_NATIVE_APP_GLUE}  ${SRC})

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${ANDROID_LIBS} ${OPENCV_LIBS} tools glestools aruco)

install(TARGETS ${PROJECT_NAME} DESTINATION ${ANAT_INSTALL_APPS}/${PROJECT_NAME}/libs/armeabi-v7a)