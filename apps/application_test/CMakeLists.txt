cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME application_test)
project(${PROJECT_NAME})

include_directories(
    ../../modules/libapplication_template/include
    )

set(SOURCES
    src/main.cpp
    src/TestApplication.cpp
    src/TestApplication.h
    )
    
add_executable(${PROJECT_NAME} ${SOURCES})

set(LIBS
    application_template
    )
target_link_libraries(${PROJECT_NAME} ${LIBS})