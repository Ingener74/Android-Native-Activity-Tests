/*
 * ErrorHandler.cpp
 *
 *  Created on: 17.03.2013
 *      Author: pavel
 */

#include "ErrorHandler.h"

const char* ErrorHandler::defaultErrorString =
		"default error string"
		;
const char* ErrorHandler::defaultSuccess =
		"success"
		;

ErrorHandler::ErrorHandler() {
}

ErrorHandler::~ErrorHandler() {
}

const char* ErrorHandler::errorString(){
	if(_isError) return _errorString;
	else         return defaultSuccess;
}

void ErrorHandler::setError(const char* errorString, bool isError ){
	_errorString = errorString;
	_isError = isError;
}
