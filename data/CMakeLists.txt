cmake_minimum_required(VERSION 2.8)

file(COPY ${CMAKE_SOURCE_DIR}/data/models DESTINATION ${CMAKE_BINARY_DIR})
configure_file(${CMAKE_SOURCE_DIR}/data/plugins.cfg.in ${CMAKE_BINARY_DIR}/models/plugins.cfg)
configure_file(${CMAKE_SOURCE_DIR}/data/resources.cfg.in ${CMAKE_BINARY_DIR}/models/resources.cfg)