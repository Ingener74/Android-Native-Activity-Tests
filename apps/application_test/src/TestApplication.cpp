/*
 * TestApplication.cpp
 *
 *  Created on: 13.07.2013
 *      Author: pavel
 */

#include "TestApplication.h"

#include "applicationtools.h"

TestApplication::TestApplication(){
}

TestApplication::~TestApplication() {
}

bool TestApplication::initialization() {
	LOG("test application initialization\n");
	return true;
}

bool TestApplication::run() {
	LOG("test application run\n");
	return true;
}

bool TestApplication::deinitialization() {
	LOG("test application deinitialization\n");
	return true;
}


