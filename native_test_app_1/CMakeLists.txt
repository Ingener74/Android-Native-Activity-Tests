cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME native1)

include_directories(
    /home/pavel/android-ndk-r8/platforms/android-14/arch-arm/usr/include
    /home/pavel/android-ndk-r8/sources/android/native_app_glue
    /home/pavel/android-ndk-r8/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/lib/gcc/arm-linux-androideabi/4.4.3/include
    )
link_directories(
    )
    
set(ANDROID_LIBS log)

set(SOURCES 
    jni/main.cpp
    jni/Log.cpp
    jni/EventLoop.cpp
    )

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${ANDROID_LIBS}) 
