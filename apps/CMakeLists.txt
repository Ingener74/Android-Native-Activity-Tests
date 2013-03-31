cmake_minimum_required(VERSION 2.8)

# apps
add_subdirectory(01_empty_application)
add_subdirectory(02_opengles10_app)
add_subdirectory(03_opencv_capture_app)
add_subdirectory(04_opengles20_app)
add_subdirectory(05_ocv_gles20_app)

# build all apps
add_custom_target(all_apps)
add_dependencies(all_apps  01_empty_application)
add_dependencies(all_apps  02_opengles10_app)
add_dependencies(all_apps  03_opencv_capture_app)
add_dependencies(all_apps  04_opengles20_app)
add_dependencies(all_apps  05_ocv_gles20_app)