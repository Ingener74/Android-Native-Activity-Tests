cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME native5)

set(ANDROID_NATIVE_APP_GLUE_DIR
    ${ANDROID_NDK}/sources/android/native_app_glue
    )

include_directories(
    ${ANDROID_NDK}/platforms/android-14/arch-arm/usr/include
    ${ANDROID_NATIVE_APP_GLUE_DIR}
    ${ANDROID_NDK}/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/lib/gcc/arm-linux-androideabi/4.4.3/include
    )
link_directories(
    ${ANDROID_NDK}/platforms/android-14/arch-arm/usr/lib
    )
set(ANDROID_LIBS log android EGL GLESv1_CM png15)

set(SOURCES
    jni/main.cpp
    jni/Log.cpp
    jni/EventLoop.cpp
    jni/ActivityHandler.cpp
    jni/DroidBlaster.cpp
    jni/TimeService.cpp
    jni/Context.cpp
    jni/GraphicsService.cpp
    ${ANDROID_NATIVE_APP_GLUE_DIR}/android_native_app_glue.c
    )

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${ANDROID_LIBS})
