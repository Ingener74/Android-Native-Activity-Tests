cmake_minimum_required(VERSION 2.8)

#include(../irwb_tools.cmake)
#print_repo_root("3rdparty cmake")
#print_current_dir()

#add_custom_target(clean_3rdparty 
#	echo "here would 3rdparty cleaner"
#	)

add_custom_target(
	build_3rdparty

	unzip -n ${CMAKE_CURRENT_LIST_DIR}/OpenCV-2.4.4-android-sdk.zip -d ${CMAKE_CURRENT_LIST_DIR} && 
	echo "================================" && 
	echo "unzip OpenCV... done"             && 
	echo "================================" 
	)
