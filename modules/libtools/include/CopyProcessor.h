/*
 * CopyProcessor.h
 *
 *  Created on: 10.03.2013
 *      Author: pavel
 */

#ifndef COPYPROCESSOR_H_
#define COPYPROCESSOR_H_

#include "IProcessor.h"

class CopyProcessor: public IProcessor {
public:
	CopyProcessor( ICaptureService* cs, IGraphicsService* gs );
	virtual ~CopyProcessor();

	bool isError(){
		return false;
	}
private:
	void process();
};

#endif /* COPYPROCESSOR_H_ */
