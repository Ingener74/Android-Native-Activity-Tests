cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME aruco_test)
project(${PROJECT_NAME})

include_directories(
    ../../modules/libaruco/include
    )

set(SOURCES 
    src/main.cpp
    )
add_executable(${PROJECT_NAME} ${SOURCES})

set(LIBS
    opencv_core
    opencv_highgui
    opencv_imgproc
    aruco
    boost_program_options
    )
target_link_libraries(${PROJECT_NAME} ${LIBS})