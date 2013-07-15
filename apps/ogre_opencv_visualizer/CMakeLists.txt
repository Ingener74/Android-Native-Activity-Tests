cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME oov)
project(${PROJECT_NAME})

set(SOURCES
    src/main.cpp 
    )
add_executable(${PROJECT_NAME} ${SOURCES})

set(LIBS
    opencv_core
    opencv_imgproc
    opencv_highgui
    boost_system
    boost_program_options
    OgreMain
    OIS
    )
target_link_libraries(${PROJECT_NAME} ${LIBS})