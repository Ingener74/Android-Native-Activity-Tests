cmake_minimum_required(VERSION 2.8)


if(ANDROID)
	add_subdirectory(libaruco)
	add_dependencies(aruco external_OpenCV)

	add_subdirectory(libglestool)
	add_dependencies(glestools external_OpenCV)

    add_subdirectory(libtools)
    add_dependencies(tools external_OpenCV)
else(ANDROID)
	add_subdirectory(libaruco)
	add_dependencies(aruco external_OpenCV)
endif(ANDROID)



