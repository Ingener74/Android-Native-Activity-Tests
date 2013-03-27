
set(REPO_HOME ${CMAKE_CURRENT_LIST_DIR})

set(ANDROID_OPENCV_DIR
    ${REPO_HOME}/3rdparty/OpenCV-2.4.4-android-sdk/sdk/native
    )

set(ANDROID_NATIVE_APP_GLUE_DIR
	${ANDROID_NDK}/sources/android/native_app_glue
    )

set(ANAT_INCLUDE
	${ANDROID_NDK}/platforms/android-14/arch-arm/usr/include
	${ANDROID_NDK}/sources/android/native_app_glue
	${ANDROID_NDK}/toolchains/arm-linux-androideabi-4.7/prebuilt/linux-x86/include
	${REPO_HOME}/3rdparty/OpenCV-2.4.4-android-sdk/sdk/native/jni/include
	)

set(ANAT_LINK
    ${ANDROID_NDK}/platforms/android-14/arch-arm/usr/lib
    ${ANDROID_OPENCV_DIR}/libs/armeabi-v7a
    ${ANDROID_OPENCV_DIR}/3rdparty/libs/armeabi-v7a
    )

set(ANAT_NATIVE_APP_GLUE ${ANDROID_NATIVE_APP_GLUE_DIR}/android_native_app_glue.c)