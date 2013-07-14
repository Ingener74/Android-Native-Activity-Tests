cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME application_template)
project(${PROJECT_NAME})

include_directories(
    include
    )

set(SOURCES 
    include/IApplication.h
    include/applicationtemplate.h
    include/applicationtools.h

    src/applicationtemplate.cpp
    src/applicationtools.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

#SET(LIBS )
#target_link_libraries(${PROJECT_NAME} ${LIBS})