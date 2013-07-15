cmake_minimum_required(VERSION 2.8)

include_directories( 
	${INSTALL_3RDPARTY}/include 
	)
link_directories( 
	${INSTALL_3RDPARTY}/lib
	)

# apps
if(ANDROID)
	#add_subdirectory(01_empty_application)
	#add_subdirectory(02_opengles10_app)
	#add_subdirectory(03_opencv_capture_app)
	#add_subdirectory(04_opengles20_app)
	add_subdirectory(05_ocv_gles20_app)
	
	add_subdirectory(android_openmax_test)

	add_subdirectory(camera_test)

else(ANDROID)
	add_subdirectory(ogre_test_001)
	add_dependencies(ogre_test_001 external_OGRE)
	add_dependencies(ogre_test_001 external_OIS)
	
	add_subdirectory(ogre_test_002)
	add_dependencies(ogre_test_002 external_OGRE)
	add_dependencies(ogre_test_002 external_OIS)
	
	add_subdirectory(ogre_test_003)
	add_dependencies(ogre_test_003 external_OGRE)
	add_dependencies(ogre_test_003 external_OIS)
	
	add_subdirectory(ogre_test)
	add_dependencies(ogre_test external_OGRE)
	add_dependencies(ogre_test external_OIS)

	add_subdirectory(application_test)
	
	add_subdirectory(aruco_test)
	
	add_subdirectory(ogre_opencv_visualizer)
	add_dependencies(ogre_test external_OpenCV)
endif(ANDROID)
