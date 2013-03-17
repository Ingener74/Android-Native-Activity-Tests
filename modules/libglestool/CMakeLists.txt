cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME glestools)
project(${PROJECT_NAME})

include_directories(
	${ANDROID_NDK}/platforms/android-14/arch-arm/usr/include
	${ANDROID_NDK}/sources/android/native_app_glue
	${ANDROID_NDK}/toolchains/arm-linux-androideabi-4.7/prebuilt/linux-x86/include
	${REPO_HOME}/3rdparty/OpenCV-2.4.4-android-sdk/sdk/native/jni/include
	${REPO_HOME}/modules/libglestool/include
    ${REPO_HOME}/modules/libtools/include
	)

set(SOURCES 
    src/AndroidGraphicBuffer.cpp
    src/EGLDispatcher.cpp
    src/FastEGLTexture.cpp
    src/GLTriangle.cpp
    src/IImageTexture.cpp
    src/IObject.cpp
    src/ITexture.cpp
    src/RGB565Texture.cpp
    src/RGBATexture.cpp
    src/RGBTexture.cpp
    src/GLMatrix4x4.cpp
    src/OBJLoader.cpp
    src/Mesh.cpp
    src/IShaderProgram.cpp
	)
set(OPENCV_LIBS
    opencv_highgui
    opencv_androidcamera
    opencv_imgproc
    opencv_core
    tbb
    libpng
    libjpeg
    libtiff
    libjasper
    IlmImf
    )

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${OPENCV_LIBS})