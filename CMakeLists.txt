cmake_minimum_required(VERSION 2.8)

set(REPO_HOME ${CMAKE_CURRENT_LIST_DIR})

message(STATUS, "android ndk directory = ${ANDROID_NDK}")

# 3rdparty
add_subdirectory(3rdparty)

# modules
add_subdirectory(modules)

# apps
add_subdirectory(apps)

# dependencies
add_dependencies(tools     build_3rdparty)
add_dependencies(glestools build_3rdparty)
add_dependencies(glestools build_3rdparty)
