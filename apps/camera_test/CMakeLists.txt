cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME camera_test)
project(${PROJECT_NAME})

include_directories(
    ../../modules/libcamera/include
    )

set(SOURCES src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} camera)
