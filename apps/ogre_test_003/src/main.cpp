/*
 * main.cpp
 *
 *  Created on: 03.05.2013
 *      Author: pavel
 */

#include <stdlib.h>
#include <iostream>

#include "TestOgreApp.h"

int main(int argc, char* argv[]) {

	std::cout << "Ogre test 003 application" << std::endl;

	if (argc == 3) {
		ogre_test_003::TestOgreApp app(argv[1], argv[2]);

		if( app.init() ){
		}

	} else {
		std::cerr
				<< "Usage: ./ogre_test_003 <path to plugin config> <path to resource config>"
				<< std::endl;
	}

	exit(EXIT_SUCCESS);
}

