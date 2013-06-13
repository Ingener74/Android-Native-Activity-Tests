cmake_minimum_required(VERSION 2.8)

include(ExternalProject)

ExternalProject_Add(
    external_glm
    URL             ${CMAKE_CURRENT_LIST_DIR}/glm-0.9.3.4.tar.gz
    CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX=${INSTALL_3RDPARTY} -DGLM_TEST_ENABLE=ON
	)

if(ANDROID)
    ExternalProject_Add(
        external_OpenCV
        URL            ${CMAKE_CURRENT_LIST_DIR}/opencv-2.4.5.tar.gz
        CMAKE_ARGS     -DCMAKE_INSTALL_PREFIX=${INSTALL_3RDPARTY} -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
		)
else(ANDROID)
    ExternalProject_Add(
        external_OpenCV
        URL            ${CMAKE_CURRENT_LIST_DIR}/opencv-2.4.5.tar.gz
        CMAKE_ARGS     -DCMAKE_INSTALL_PREFIX=${INSTALL_3RDPARTY}
        )

    ExternalProject_Add(
        external_OGRE
        URL ${CMAKE_CURRENT_LIST_DIR}/ogre_src_v1-8-1.tar.bz2
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${INSTALL_3RDPARTY} -DOGRE_INSTALL_SAMPLES=YES
        )

    set(EXTERNAL_PROJECT_OIS external_OIS)
    ExternalProject_Add(
        external_OIS
        URL ${CMAKE_CURRENT_LIST_DIR}/ois_v1-3.tar.gz
        PATCH_COMMAND patch -p1 < ${CMAKE_CURRENT_LIST_DIR}/ois.patch
        BINARY_DIR ${CMAKE_BINARY_DIR}/3rdparty/${EXTERNAL_PROJECT_OIS}-prefix/src/${EXTERNAL_PROJECT_OIS}
        CONFIGURE_COMMAND sh ${CMAKE_BINARY_DIR}/3rdparty/${EXTERNAL_PROJECT_OIS}-prefix/src/${EXTERNAL_PROJECT_OIS}/bootstrap && 
            ${CMAKE_BINARY_DIR}/3rdparty/${EXTERNAL_PROJECT_OIS}-prefix/src/${EXTERNAL_PROJECT_OIS}/configure --prefix=${INSTALL_3RDPARTY}
        )
endif(ANDROID)

