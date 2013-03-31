cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME 02_opengles10_app)
project(${PROJECT_NAME})

include_directories(
    ${ANAT_INCLUDE}
    ../../modules/libtools/include
    ../../modules/libglestool/include
    )
link_directories(
    ${ANAT_LINK}
    )
set(ANDROID_LIBS 
    log 
    android
    z
    
    EGL
    GLESv1_CM
    
    opencv_core
    opencv_highgui
    opencv_imgproc
    
    tbb
    IlmImf
    libjasper
    libjpeg
    libpng
    libtiff
    )

file(GLOB SRC src/*.cpp)
set(SOURCES  ${ANAT_NATIVE_APP_GLUE}  ${SRC})

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${ANDROID_LIBS} tools glestools)

install(TARGETS ${PROJECT_NAME} DESTINATION ${ANAT_INSTALL}/${PROJECT_NAME}/libs/armeabi-v7a)