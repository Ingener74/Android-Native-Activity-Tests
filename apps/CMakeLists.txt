cmake_minimum_required(VERSION 2.8)

# apps
if(ANDROID)
	add_subdirectory(01_empty_application)
	add_subdirectory(02_opengles10_app)
	add_subdirectory(03_opencv_capture_app)
	add_subdirectory(04_opengles20_app)
	add_subdirectory(05_ocv_gles20_app)

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
	
	add_subdirectory(06_OGRE_Test)
	add_dependencies(06_OGRETest external_OGRE)
	add_dependencies(06_OGRETest external_OIS)
endif(ANDROID)
