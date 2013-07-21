cmake_minimum_required(VERSION 2.8)

include(ExternalProject)

# glm
set(EXTERNAL_GLM external_glm)
ExternalProject_Add(
    ${EXTERNAL_GLM}
    URL             ${CMAKE_CURRENT_LIST_DIR}/glm-0.9.3.4.tar.gz
    CONFIGURE_COMMAND ""
    CMAKE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND cp -R ${CMAKE_BINARY_DIR}/3rdparty/${EXTERNAL_GLM}-prefix/src/${EXTERNAL_GLM}/glm ${INSTALL_3RDPARTY}/include
	)

if(ANDROID)
    ExternalProject_Add(
        external_OpenCV
        URL            ${CMAKE_CURRENT_LIST_DIR}/opencv-2.4.5.tar.gz
        CMAKE_ARGS     -DCMAKE_INSTALL_PREFIX=${INSTALL_3RDPARTY} -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
		)
else(ANDROID)
    # OpenCV
    ExternalProject_Add(
        external_OpenCV
        URL            ${CMAKE_CURRENT_LIST_DIR}/opencv-2.4.5.tar.gz
        CMAKE_ARGS     -DCMAKE_INSTALL_PREFIX=${INSTALL_3RDPARTY}
        )

    # boost
    set(EXTERNAL_BOOST external_boost)
    ExternalProject_Add(
        ${EXTERNAL_BOOST}
        URL ${CMAKE_CURRENT_LIST_DIR}/boost_1_54_0.zip
        CONFIGURE_COMMAND cd ${CMAKE_BINARY_DIR}/3rdparty/${EXTERNAL_BOOST}-prefix/src/${EXTERNAL_BOOST} && ./bootstrap.sh
        CMAKE_COMMAND ""
        BUILD_COMMAND cd ${CMAKE_BINARY_DIR}/3rdparty/${EXTERNAL_BOOST}-prefix/src/${EXTERNAL_BOOST} && ./b2 install --prefix=${INSTALL_3RDPARTY} link=static
        INSTALL_COMMAND ""
        )
        
    # OGRE
    ExternalProject_Add(
        external_OGRE
        URL ${CMAKE_CURRENT_LIST_DIR}/ogre_src_v1-8-1.tar.bz2
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${INSTALL_3RDPARTY} -DOGRE_INSTALL_SAMPLES=YES -DBoost_DIR=${INSTALL_3RDPARTY}#/include
        )
	add_dependencies(external_OGRE ${EXTERNAL_BOOST})

    # OIS
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

