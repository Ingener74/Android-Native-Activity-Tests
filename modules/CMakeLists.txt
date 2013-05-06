cmake_minimum_required(VERSION 2.8)


if(ANDROID)
    #add_subdirectory(libglestool)
else(ANDROID)
    #add_subdirectory(libtools)
    add_subdirectory(libaruco)
    add_dependencies(aruco external_OpenCV)
endif(ANDROID)



