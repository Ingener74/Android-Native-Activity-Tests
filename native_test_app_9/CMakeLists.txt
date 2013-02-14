cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME native9)

set(ANDROID_NATIVE_APP_GLUE_DIR
    ${ANDROID_NDK}/sources/android/native_app_glue
    )

include_directories(
    ${ANDROID_NDK}/platforms/android-14/arch-arm/usr/include
    ${ANDROID_NATIVE_APP_GLUE_DIR}
    ${ANDROID_NDK}/toolchains/arm-linux-androideabi-4.7/prebuilt/linux-x86/include
    /home/pavel/prj/OpenCV-2.4.4-android-sdk/sdk/native/jni/include
    )
link_directories(
    ${ANDROID_NDK}/platforms/android-14/arch-arm/usr/lib
    /home/pavel/prj/OpenCV-2.4.4-android-sdk/sdk/native/libs/armeabi-v7a
    /home/pavel/prj/OpenCV-2.4.4-android-sdk/sdk/native/3rdparty/libs/armeabi-v7a
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

set(SOURCES
    ${ANDROID_NATIVE_APP_GLUE_DIR}/android_native_app_glue.c
    jni/main.cpp
    jni/GraphicsService.cpp
    jni/IGraphicsObject.cpp
    jni/Point.cpp
    jni/Triangle.cpp
    )

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${ANDROID_LIBS} ${OPENCV_LIBS})
