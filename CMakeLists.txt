cmake_minimum_required(VERSION 2.8)

set(INSTALL_3RDPARTY ${CMAKE_BINARY_DIR}/INSTALL_3RDPARTY)

# 3rdparty
add_subdirectory(3rdparty)

# modules
add_subdirectory(modules)

# apps
add_subdirectory(apps)
