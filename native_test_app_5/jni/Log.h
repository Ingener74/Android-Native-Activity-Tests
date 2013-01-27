/*
 * Log.h
 *
 *  Created on: 25.01.2013
 *      Author: pavel
 */

#ifndef LOG_H_
#define LOG_H_

#include <stdarg.h>
#include <android/log.h>

namespace smallarsdk {

class Log {
public:
	static void error( const char* message, ... );
	static void warn ( const char* message, ... );
	static void info ( const char* message, ... );
	static void debug( const char* message, ... );
};

}

#ifndef NDEBUG
#define smallarsdk_Log_debug(...) smallarsdk::Log::debug(__VA_ARGS__)
#else
#define smallarsdk_Log_debug(...)
#endif

#endif /* LOG_H_ */
