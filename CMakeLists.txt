cmake_minimum_required(VERSION 2.8)

# root dir
set(AR_ROOT ${CMAKE_CURRENT_LIST_DIR})

# install dir
set(AR_INSTALL ${AR_ROOT}/linux_install CACHE TYPE PATH)

# set cmake install prefix to install dir
set(CMAKE_INSTALL_PREFIX ${AR_INSTALL})

# 3rdparty
add_subdirectory(3rdparty)

# modules
add_subdirectory(modules)

# apps
add_subdirectory(apps)
