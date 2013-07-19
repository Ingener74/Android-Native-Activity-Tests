cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME ogre_test_003)
project(${PROJECT_NAME})

file(GLOB app_src src/*.cpp)
file(GLOB app_hdr src/*.h)

add_executable(${PROJECT_NAME} ${app_src} ${app_hdr})
target_link_libraries(${PROJECT_NAME} OgreMain boost_system)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
