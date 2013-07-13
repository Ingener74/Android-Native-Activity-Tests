/*
 * main.cpp
 *
 *  Created on: 13.07.2013
 *      Author: pavel
 */


#include <IApplication.h>
#include <applicationtools.h>
#include <applicationtemplate.h>

#include "TestApplication.h"

int main(int argc, char* argv[]) {

	are::application::IApplication* _app = new TestApplication();

	if (_app) {
		if( _app->initialization() ){
			if( !_app->run() ){
				LOG("application run return with error");
			}
		}else{
			LOG("can't initialize application");
			APPLICATION_EXIT_FAILURE;
		}
	} else {
		LOG("can't create application");
		APPLICATION_EXIT_FAILURE;
	}

	return 0;
}

