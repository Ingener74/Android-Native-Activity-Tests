cmake_minimum_required(VERSION 2.8)

#add_subdirectory(libtools)
#add_subdirectory(libglestool)
add_subdirectory(libaruco)

add_dependencies(aruco external_OpenCV)

