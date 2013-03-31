cmake_minimum_required(VERSION 2.8)

include(../anat_tools.cmake)

add_custom_target(
	build_opencv

	echo "================================" &&
	echo "unzip OpenCV..."                  &&
    mkdir -p ${ANAT_INSTALL_3RDPARTY}       &&
	unzip -n ${CMAKE_CURRENT_LIST_DIR}/OpenCV-2.4.4-android-sdk.zip -d ${ANAT_INSTALL_3RDPARTY} &&
	echo "done"                             &&
	echo "================================"
	)
	
add_custom_target(
    build_glm
    
    echo "================================" &&
	echo "unzip glm..."                     &&
	mkdir -p ${ANAT_INSTALL_3RDPARTY}       &&
    unzip -n ${CMAKE_CURRENT_LIST_DIR}/glm-0.9.4.zip -d ${ANAT_INSTALL_3RDPARTY} &&
    echo "done"                             &&
	echo "================================"
    )
    
add_custom_target(all_3rdparty)
add_dependencies(all_3rdparty build_opencv)
add_dependencies(all_3rdparty build_glm)