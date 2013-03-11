/*
 * IProcessor.cpp
 *
 *  Created on: 18.02.2013
 *      Author: pavel
 */

#include "IProcessor.h"

IProcessor::IProcessor( ICaptureService* cs, IGraphicsService* gs )
	: _cs(cs), _gs(gs){

	LOGI("IProcessor", "constructor begin");
	if(_cs && _gs){
//		pthread_mutex_init(&_stop_mutex, NULL);

		LOGI("IProcessor", "cs = %d, gs = %d", _cs, _gs);
	}else{
		LOGE("IProcessor", "cs = %d, gs = %d", _cs, _gs);
	}
	LOGI("IProcessor", "constructor end");
}

IProcessor::~IProcessor(){
//	pthread_mutex_destroy(&_stop_mutex);
}

void IProcessor::start(){
//	int ret = pthread_create(&_thread, 0, &IProcessor::staticProcess, (void*)this);
//	if(!ret){
//		LOGI("IProcessor", "thread started");
//	}
}

void IProcessor::stop(){
//	pthread_mutex_lock(&_stop_mutex);
//	_stop = true;
//	pthread_mutex_unlock(&_stop_mutex);
}

void* IProcessor::staticProcess( void* this_ ){
//	while(1){
//
//		OGLESExecTime t;
//		((IProcessor*)this_)->process();
//		t.print("Processor");
//
//		pthread_mutex_lock( &((IProcessor*)this_)->_stop_mutex );
//		if( ((IProcessor*)this_)->_stop ){
//			LOGI("IProcessor", "Processor stopped");
//			return 0;
//		}
//		pthread_mutex_unlock( &((IProcessor*)this_)->_stop_mutex );
//	}

	return NULL;
}
