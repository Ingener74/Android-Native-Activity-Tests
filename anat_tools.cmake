
set(REPO_HOME ${CMAKE_CURRENT_LIST_DIR})

set(ANAT_BUILD_DIR ${CMAKE_BINARY_DIR})

# Android native-activity test install directory
IF(${ANDROID})
    SET(ANAT_INSTALL ${REPO_HOME}/android_build)
ELSE(${ANDROID})
    SET(ANAT_INSTALL ${REPO_HOME}/${CMAKE_SYSTEM_NAME}_build)
ENDIF(${ANDROID})

# Android native-activity test install 3rdparty directory
set(ANAT_INSTALL_3RDPARTY ${ANAT_INSTALL}/3rdparty)

# Android native-activity test install application directory
set(ANAT_INSTALL_APPS     ${ANAT_INSTALL}/apps)

# Android OpenCV directory
set(ANDROID_OPENCV_DIR
    ${ANAT_INSTALL_3RDPARTY}/OpenCV-2.4.4-android-sdk/sdk/native
    )
    
set(GLM_DIR
    ${ANAT_INSTALL_3RDPARTY}/glm-0.9.4
    )

# Android native app glue source file
set(ANDROID_NATIVE_APP_GLUE_DIR
	${ANDROID_NDK}/sources/android/native_app_glue
    )

# Android include directories
set(ANAT_INCLUDE
	${ANDROID_NDK}/platforms/android-14/arch-arm/usr/include
	${ANDROID_NDK}/sources/android/native_app_glue
	${ANDROID_NDK}/toolchains/arm-linux-androideabi-4.7/prebuilt/linux-x86/include
	${ANDROID_OPENCV_DIR}/jni/include
	${GLM_DIR}
	)

# Android link directories
set(ANAT_LINK
    ${ANDROID_NDK}/platforms/android-14/arch-arm/usr/lib
    ${ANDROID_OPENCV_DIR}/libs/armeabi-v7a
    ${ANDROID_OPENCV_DIR}/3rdparty/libs/armeabi-v7a
    )

set(ANAT_NATIVE_APP_GLUE ${ANDROID_NATIVE_APP_GLUE_DIR}/android_native_app_glue.c)

macro(print_information)
    message("REPO_HOME                    = ${REPO_HOME}")
    message("ANDROID_OPENCV_DIR           = ${ANDROID_OPENCV_DIR}")
    message("ANDROID_NDK                  = ${ANDROID_NDK}")
    message("ANDROID_NATIVE_APP_GLUE_DIR  = ${ANDROID_NATIVE_APP_GLUE_DIR}")
    message("ANAT_INCLUDE                 = ${ANAT_INCLUDE}")
    message("ANAT_LINK                    = ${ANAT_LINK}")
    message("ANAT_BUILD_DIR               = ${ANAT_BUILD_DIR}")
    message("ANAT_INSTALL                 = ${ANAT_INSTALL}")
    message("ANAT_INSTALL_3RDPARTY        = ${ANAT_INSTALL_3RDPARTY}")
endmacro(print_information)