cmake_minimum_required(VERSION 2.8)

add_subdirectory(libtools)
add_subdirectory(libglestool)
add_subdirectory(libaruco)

# build all_modules
add_custom_target(all_modules)
add_dependencies(all_modules  tools)
add_dependencies(all_modules  glestools)
add_dependencies(all_modules  aruco)