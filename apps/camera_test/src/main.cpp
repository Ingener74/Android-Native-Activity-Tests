

#include <iostream>

#include <yuv.h>
#include <util.h>
#include <video_device.h>
#include <capture.h>

int main( int argc, char* argv[] ){

	std::cout << "Native camera test" << std::endl;

	static int DEVICE_DESCRIPTOR = -1;
	int* RGB_BUFFER = NULL;
	int* Y_BUFFER = NULL;

	const char* device = "/dev/video0";

	int result = open_device(device, &DEVICE_DESCRIPTOR);
	if(result == ERROR_LOCAL) {
		return result;
		std::cout << "can't open " << device << std::endl;
	}else{
		std::cout << device << " opened" << std::endl;
	}

	int width = 600, height = 800;

	result = init_device(DEVICE_DESCRIPTOR, width, height);
	if(result == ERROR_LOCAL) {
		return result;
		std::cout << "can't init device on " << width << "x" << height << std::endl;
	}else{
		std::cout << "device on " << width << "x" << height << std::endl;
	}

	result = start_capture(DEVICE_DESCRIPTOR);
	if(result != SUCCESS_LOCAL) {
		stop_camera(&DEVICE_DESCRIPTOR, RGB_BUFFER, Y_BUFFER);
		std::cout << "can't start capture" << std::endl;
	} else {
		int area = width * height;
		RGB_BUFFER = (int*)malloc(sizeof(int) * area);
		Y_BUFFER = (int*)malloc(sizeof(int) * area);

		std::cout << "=== buffer ===" << std::endl;

		for ( int i = 0; i < 10; ++i ){
			std::cout << RGB_BUFFER[i] << std::endl;
		}
	}

	for( int i = 0; i < 100; ++i ){
		process_camera(DEVICE_DESCRIPTOR, FRAME_BUFFERS, info.width, info.height,
					RGB_BUFFER, Y_BUFFER);
	}

	stop_camera(&DEVICE_DESCRIPTOR, RGB_BUFFER, Y_BUFFER);
	return 0;
}
