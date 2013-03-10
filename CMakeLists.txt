cmake_minimum_required(VERSION 2.8)

set(REPO_HOME ${CMAKE_CURRENT_LIST_DIR})
#message("repo dir = "${REPO_HOME})

# modules
add_subdirectory(modules)

# apps
add_subdirectory(apps)
