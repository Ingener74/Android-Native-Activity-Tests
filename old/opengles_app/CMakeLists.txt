cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME opengles_test)

set(REPO_ROOT 
    /home/ingener/prj/Android-Native-Activity-Tests
    )

set(ANDROID_NATIVE_APP_GLUE_DIR
    ${ANDROID_NDK}/sources/android/native_app_glue
    )
    
set(ANDROID_OPENCV_DIR
    ${REPO_ROOT}/3rdparty/OpenCV-2.4.4-android-sdk/sdk/native
    #/home/pavel/prj/android_tut/3rdparty/OpenCV-2.4.4-android-sdk/sdk/native
    )

include_directories(
    ${ANDROID_NDK}/platforms/android-14/arch-arm/usr/include
    ${ANDROID_NATIVE_APP_GLUE_DIR}
    ${ANDROID_NDK}/toolchains/arm-linux-androideabi-4.7/prebuilt/linux-x86/include
    ${ANDROID_OPENCV_DIR}/jni/include
    ${REPO_ROOT}/modules/libtools/include    
    )
link_directories(
    ${ANDROID_NDK}/platforms/android-14/arch-arm/usr/lib
    ${ANDROID_OPENCV_DIR}/libs/armeabi-v7a
    ${ANDROID_OPENCV_DIR}/3rdparty/libs/armeabi-v7a
    ${REPO_ROOT}/libs/armeabi-v7a
    )
set(ANDROID_LIBS 
    log 
    android 
    EGL 
    GLESv1_CM
    z
    )
set(OPENCV_LIBS 
    opencv_core
    opencv_highgui
    opencv_androidcamera
    opencv_imgproc
    tbb
    libpng
    libjpeg
    libtiff
    libjasper
    IlmImf
    )
    
set(MY_LIBS
    tools
    )

set(SOURCES
    ${ANDROID_NATIVE_APP_GLUE_DIR}/android_native_app_glue.c
    jni/main.cpp    
    jni/OpenGLESTestEventEngine.cpp
    jni/OpenGLES100GraphicsService.cpp
    jni/NativeWindowGraphicsService.cpp    
    )

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${EXT_SOURCES})
target_link_libraries(${PROJECT_NAME} ${ANDROID_LIBS} ${OPENCV_LIBS} ${MY_LIBS})
