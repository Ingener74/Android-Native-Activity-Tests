cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME openmax_test)
project(${PROJECT_NAME})

set(SOURCES src/main.cpp)

include_directories(
    ${ANDROID_NDK}/platforms/android-14/arch-arm/usr/include
	)
link_directories(
    ${ANDROID_NDK}/platforms/android-14/arch-arm/usr/lib
    )

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} OpenMAXAL)
