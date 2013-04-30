cmake_minimum_required(VERSION 2.8)

include(ExternalProject)

ExternalProject_Add(
	external_glm
	GIT_REPOSITORY  git://github.com/Groovounet/glm.git
	GIT_TAG         0.9.3.4
	CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}/3rdparty -DGLM_TEST_ENABLE=ON
	)

if(ANDROID)
else(ANDROID)
	ExternalProject_Add(
		external_OpenCV
		GIT_REPOSITORY git://github.com/Itseez/opencv.git
		GIT_TAG        2.4.5
		CMAKE_ARGS     -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}/3rdparty
		)

    # prerequisites
    # Compiler And Configuration Tools:    sudo apt-get install build-essential automake libtool
    # Required Dependencies:               sudo apt-get install libfreetype6-dev libfreeimage-dev libzzip-dev libxrandr-dev libxaw7-dev freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev
    # Not Strictly Required Dependencies:  sudo apt-get install nvidia-cg-toolkit libois-dev libboost-thread-dev
    # Entirely Optional Dependencies:      sudo apt-get install doxygen graphviz libcppunit-dev
    ExternalProject_Add(
        external_OGRE
        URL ${CMAKE_CURRENT_LIST_DIR}/ogre_src_v1-8-1.tar.bz2
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}/3rdparty
        )
endif(ANDROID)

