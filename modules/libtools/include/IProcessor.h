/*
 * IProcessor.h
 *
 *  Created on: 18.02.2013
 *      Author: pavel
 */

#ifndef IPROCESSOR_H_
#define IPROCESSOR_H_

//#include <boost/thread.hpp>
#include <pthread.h>

#include "IService.h"
#include "ICaptureService.h"
#include "IGraphicsService.h"
#include "tools.h"

class IProcessor: public IService {
public:
	IProcessor( ICaptureService* cs = NULL, IGraphicsService* gs = NULL );
	virtual ~IProcessor();

	virtual void process() = 0;
	void         start();
	void         stop();

protected:
	static void*      staticProcess( void* this_ );

	ICaptureService*  _cs;
	IGraphicsService* _gs;

//	pthread_t         _thread;
//	pthread_mutex_t   _stop_mutex;
//	bool              _stop;
};

#endif /* IPROCESSOR_H_ */
