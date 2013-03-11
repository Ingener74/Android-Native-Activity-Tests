cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME 03_opencv_capture_app)

set(ANDROID_NATIVE_APP_GLUE_DIR
    ${ANDROID_NDK}/sources/android/native_app_glue
    )
    
set(ANDROID_OPENCV_DIR
    ${REPO_HOME}/3rdparty/OpenCV-2.4.4-android-sdk/sdk/native
    )

include_directories(
    ${ANDROID_NDK}/platforms/android-14/arch-arm/usr/include
    ${ANDROID_NATIVE_APP_GLUE_DIR}
    ${ANDROID_NDK}/toolchains/arm-linux-androideabi-4.7/prebuilt/linux-x86/include
    ${ANDROID_OPENCV_DIR}/jni/include
    
    ${REPO_HOME}/modules/libtools/include
    )
link_directories(
    ${ANDROID_NDK}/platforms/android-14/arch-arm/usr/lib
    ${ANDROID_OPENCV_DIR}/libs/armeabi-v7a
    ${ANDROID_OPENCV_DIR}/3rdparty/libs/armeabi-v7a
    ${REPO_HOME}/libs/armeabi-v7a
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

set(SOURCES
    ${ANDROID_NATIVE_APP_GLUE_DIR}/android_native_app_glue.c
    src/main.cpp
    src/OpenCVCaptureEventHandler.cpp
    src/OpenCVCaptureGraphicsService.cpp
    )

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${ANDROID_LIBS} tools)

install(TARGETS ${PROJECT_NAME} DESTINATION ${REPO_HOME}/android_build/${PROJECT_NAME}/libs/armeabi-v7a)