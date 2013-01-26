/*
 * Log.cpp
 *
 *  Created on: 25.01.2013
 *      Author: pavel
 */

#include "Log.h"

namespace smallarsdk {

void Log::error( const char* message, ... ){
	va_list vars;
	va_start(vars, message);
	__android_log_vprint(ANDROID_LOG_ERROR, "SmallARSDK", message, vars);
	__android_log_print(ANDROID_LOG_ERROR, "SmallARSDK", "\n");
	va_end(vars);
}
void Log::warn( const char* message, ... ){
	va_list vars;
	va_start(vars, message);
	__android_log_vprint(ANDROID_LOG_WARN, "SmallARSDK", message, vars);
	__android_log_print(ANDROID_LOG_WARN, "SmallARSDK", "\n");
	va_end(vars);
}

void Log::info( const char* message, ... ){
	va_list vars;
	va_start(vars, message);
	__android_log_vprint(ANDROID_LOG_INFO, "SmallARSDK", message, vars);
	__android_log_print(ANDROID_LOG_INFO, "SmallARSDK", "\n");
	va_end(vars);
}

void Log::debug( const char* message, ... ){
	va_list vars;
	va_start(vars, message);
	__android_log_vprint(ANDROID_LOG_DEBUG, "SmallARSDK", message, vars);
	__android_log_print(ANDROID_LOG_DEBUG, "SmallARSDK", "\n");
	va_end(vars);
}

}
