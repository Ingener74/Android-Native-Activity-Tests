cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME application)
project(${PROJECT_NAME})

set(SOURCES 
    include/IApplication.h)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

SET(LIBS )
target_link_libraries(${PROJECT_NAME} ${LIBS})