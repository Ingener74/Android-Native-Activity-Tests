cmake_minimum_required(VERSION 2.8)

include(anat_tools.cmake)

print_information()

# 3rdparty
add_subdirectory(3rdparty)

# modules
add_subdirectory(modules)

# apps
add_subdirectory(apps)

# dependencies
add_dependencies(tools     build_3rdparty)
add_dependencies(glestools build_3rdparty)
add_dependencies(aruco     build_3rdparty)
