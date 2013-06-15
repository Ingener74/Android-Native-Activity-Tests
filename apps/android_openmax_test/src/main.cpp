/*
 * main.cpp
 *
 *  Created on: 15.06.2013
 *      Author: pavel
 */

#include <cstdlib>
#include <iostream>

#include <OMXAL/OpenMAXAL.h>
#include <OMXAL/OpenMAXAL_Android.h>

// from OpenMAX 1.1
#define XA_ENGINEOPTION_MAJORVERSION    ((XAuint32) 0x00000003)
#define XA_ENGINEOPTION_MINORVERSION    ((XAuint32) 0x00000004)

const char* results[] = {
	"XA_RESULT_SUCCESS               ", 
	"XA_RESULT_PRECONDITIONS_VIOLATED", 
	"XA_RESULT_PARAMETER_INVALID     ", 
	"XA_RESULT_MEMORY_FAILURE        ", 
	"XA_RESULT_RESOURCE_ERROR        ", 
	"XA_RESULT_RESOURCE_LOST         ", 
	"XA_RESULT_IO_ERROR              ", 
	"XA_RESULT_BUFFER_INSUFFICIENT   ", 
	"XA_RESULT_CONTENT_CORRUPTED     ", 
	"XA_RESULT_CONTENT_UNSUPPORTED   ", 
	"XA_RESULT_CONTENT_NOT_FOUND     ", 
	"XA_RESULT_PERMISSION_DENIED     ", 
	"XA_RESULT_FEATURE_UNSUPPORTED   ", 
	"XA_RESULT_INTERNAL_ERROR        ", 
	"XA_RESULT_UNKNOWN_ERROR         ", 
	"XA_RESULT_OPERATION_ABORTED     ", 
	"XA_RESULT_CONTROL_LOST          ", 
};

#define check_err(x, m){\
	if(x!=XA_RESULT_SUCCESS) {\
		std::cout << m << " - > " << results[x] << std::endl; \
		exit(EXIT_FAILURE);\
	} \
	}

int main( int argc, char* argv[] ){

	std::cout << "Android OpenMAX test" << std::endl;

	XAObjectItf engine;
	XAEngineOption engineOptions[] = {
			(XAuint32)XA_ENGINEOPTION_THREADSAFE, (XAuint32) XA_BOOLEAN_TRUE,
			(XAuint32)XA_ENGINEOPTION_MAJORVERSION, (XAuint32)1,
			(XAuint32)XA_ENGINEOPTION_MINORVERSION, (XAuint32)1
	};

	XAresult r = xaCreateEngine(&engine, 1, engineOptions, 0, NULL, NULL);
	check_err(r, "can't create engine");

	r = (*engine)->Realize(engine, XA_BOOLEAN_FALSE);
	check_err(r, "can't realize engine");

	XAEngineItf engineItf;
	r = (*engine)->GetInterface(engine, XA_IID_ENGINE, (void*)&engineItf);
	check_err(r, "can't get engine interface");

	XAObjectItf camera;
	r = (*engineItf)->CreateCameraDevice(engineItf, &camera, XA_DEFAULTDEVICEID_CAMERA, 0, NULL, NULL);
	check_err(r, "can't create camera device");

	(*camera)->Destroy(camera);
	(*engine)->Destroy(engine);

	std::cout << "exit" << std::endl;

	return 0;
}

