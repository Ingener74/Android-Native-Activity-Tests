cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME ogre_test_002)
project(${PROJECT_NAME})

set(SOURCES src/TinyOgre.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} OgreMain boost_system)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
