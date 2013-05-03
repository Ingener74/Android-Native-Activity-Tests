cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME ogre_test_002)
project(${PROJECT_NAME})

include_directories(
    ${CMAKE_INSTALL_PREFIX}/3rdparty/include
    )
link_directories(
    ${CMAKE_INSTALL_PREFIX}/3rdparty/lib
    )

set(SOURCES src/TinyOgre.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} OgreMain)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)