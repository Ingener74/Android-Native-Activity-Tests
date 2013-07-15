cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME ogre_test)
project(${PROJECT_NAME})

file(COPY ${CMAKE_SOURCE_DIR}/data/apps/ogre_test/Kubelwagen DESTINATION ${CMAKE_BINARY_DIR}/data/apps/ogre_test/)
configure_file(${CMAKE_SOURCE_DIR}/data/apps/ogre_test/plugins.cfg.in ${CMAKE_BINARY_DIR}/data/apps/ogre_test/plugins.cfg)
configure_file(${CMAKE_SOURCE_DIR}/data/apps/ogre_test/resources.cfg.in ${CMAKE_BINARY_DIR}/data/apps/ogre_test/resources.cfg)

file(GLOB app_src src/*.cpp)
file(GLOB app_hdr src/*.h)

add_executable(${PROJECT_NAME} ${app_src} ${app_hdr})
target_link_libraries(${PROJECT_NAME} OgreMain OIS boost_system boost_program_options)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
