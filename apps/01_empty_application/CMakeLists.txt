cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME 01_empty_application)
project(${PROJECT_NAME})

include(../../anat_tools.cmake)

include_directories(
    ${ANAT_INCLUDE}
    ../../modules/libtools/include
    )
link_directories(
    ${ANAT_LINK}
    ${REPO_HOME}/libs/armeabi-v7a
    )
set(ANDROID_LIBS
    log
    android

    opencv_core
    opencv_highgui
    opencv_imgproc
    )

file(GLOB SRC src/*.cpp)
set(SOURCES  ${ANAT_NATIVE_APP_GLUE}  ${SRC})

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${ANDROID_LIBS} tools)

install(TARGETS ${PROJECT_NAME} DESTINATION ${REPO_HOME}/android_build/${PROJECT_NAME}/libs/armeabi-v7a)
