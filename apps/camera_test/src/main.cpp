

#include <iostream>
#include <camera.h>

int *rgb;

int main( int argc, char* argv[] ){

	std::cout << "Native camera test" << std::endl;

	if( camera::Camera::prepareCamera(0) != ERROR_LOCAL ){
		std::cout << "success" << std::endl;

		camera::Camera::processCamera();

		if( rgb ){

			for( int i = 0; i < 10; ++i ){
				std::cout << rgb[i] << std::endl;
			}

		}

		camera::Camera::stopCamera();

	}else{
		std::cout << "error" << std::endl;
	}
	std::cout << "exit" << std::endl;
	return 0;
}
