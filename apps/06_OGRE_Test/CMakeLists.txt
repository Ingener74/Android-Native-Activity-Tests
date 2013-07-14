cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME 06_OGRETest)
project(${PROJECT_NAME})

file(COPY ${CMAKE_SOURCE_DIR}/data/apps/06_OGRE_Test/Kubelwagen DESTINATION ${CMAKE_BINARY_DIR}/data/apps/06_OGRE_Test/)
configure_file(${CMAKE_SOURCE_DIR}/data/apps/06_OGRE_Test/plugins.cfg.in ${CMAKE_BINARY_DIR}/data/apps/06_OGRE_Test/plugins.cfg)
configure_file(${CMAKE_SOURCE_DIR}/data/apps/06_OGRE_Test/resources.cfg.in ${CMAKE_BINARY_DIR}/data/apps/06_OGRE_Test/resources.cfg)

file(GLOB app_src src/*.cpp)
file(GLOB app_hdr src/*.h)

add_executable(${PROJECT_NAME} ${app_src} ${app_hdr})
target_link_libraries(${PROJECT_NAME} OgreMain OIS)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
