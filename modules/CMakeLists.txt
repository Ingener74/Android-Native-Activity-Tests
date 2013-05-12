cmake_minimum_required(VERSION 2.8)

include_directories( 
	${INSTALL_3RDPARTY}/include 
	)
link_directories( 
	${INSTALL_3RDPARTY}/lib
	)

#add_subdirectory(libtools)
#add_subdirectory(libglestool)
add_subdirectory(libaruco)

add_dependencies(aruco external_OpenCV)

