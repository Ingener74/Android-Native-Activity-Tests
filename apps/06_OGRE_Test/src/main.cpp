/*
 * main.cpp
 *
 *  Created on: 04.05.2013
 *      Author: pavel
 */

#include <iostream>

#include "OGRETestApp.h"

int main( int argc, char* argv[] ){

	std::cout << "OGRE Test application" << std::endl;

	if( argc == 3 ){
		ogre_test::OGRETestApp app(argv[1], argv[2]);

		app.run();
	}else{
		std::cerr << "Usage: ./06_OGRETest <path to plugin config> <path to resource config>" << std::endl;
	}

	return 0;
}


