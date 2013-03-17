/*
 * ErrorHandler.h
 *
 *  Created on: 17.03.2013
 *      Author: pavel
 */

#ifndef ERRORHANDLER_H_
#define ERRORHANDLER_H_

class ErrorHandler {
public:
	ErrorHandler();
	virtual ~ErrorHandler();

	virtual bool isError(){ return _isError; }
	virtual const char* errorString();
	virtual void setError( const char* errorString, bool isError = true );

private:
	bool  _isError;
	char* _errorString;

	static const char* defaultErrorString;
	static const char* defaultSuccess;
};

#endif /* ERRORHANDLER_H_ */
