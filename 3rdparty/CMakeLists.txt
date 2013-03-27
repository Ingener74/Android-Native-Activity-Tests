cmake_minimum_required(VERSION 2.8)

include(../anat_tools.cmake)

add_custom_target(
	build_3rdparty

	unzip -n ${CMAKE_CURRENT_LIST_DIR}/OpenCV-2.4.4-android-sdk.zip -d ${CMAKE_CURRENT_LIST_DIR} &&
	echo "================================" &&
	echo "unzip OpenCV... done"             &&
	echo "================================"
	)
