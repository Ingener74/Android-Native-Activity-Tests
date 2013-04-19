cmake_minimum_required(VERSION 2.8)

include(../anat_tools.cmake)

include(ExternalProject)

ExternalProject_Add(
	external_glm
	GIT_REPOSITORY  git://github.com/Groovounet/glm.git
	GIT_TAG         0.9.3.4
	CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX=${ANAT_INSTALL} -DGLM_TEST_ENABLE=ON
#	BUILD_COMMAND   ""
#	INSTALL_COMMAND ""
	)

if(ANDROID)
else(ANDROID)
	ExternalProject_Add(
		external_OpenCV
		GIT_REPOSITORY git://github.com/Itseez/opencv.git
		GIT_TAG        2.4.5
		CMAKE_ARGS     -DCMAKE_INSTALL_PREFIX=${ANAT_INSTALL}
		)
endif(ANDROID)

