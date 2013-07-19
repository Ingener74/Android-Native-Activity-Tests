cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME ogre_test_001)
project(${PROJECT_NAME})

set(SOURCES 
    src/main.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
target_link_libraries(${PROJECT_NAME} OgreMain boost_system)
