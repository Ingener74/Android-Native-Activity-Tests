/*
 * CircleProcessor.h
 *
 *  Created on: 18.02.2013
 *      Author: pavel
 */

#ifndef CIRCLEPROCESSOR_H_
#define CIRCLEPROCESSOR_H_

#include "IProcessor.h"
#include "tools.h"

#include "OpenCVCapture.h"

class CircleProcessor: public IProcessor {
public:
	CircleProcessor( ICaptureService* captureService = NULL,
			IGraphicsService* graphService = NULL);
	virtual ~CircleProcessor();

	bool isError(){
		return false;
	}

protected:
	virtual void process();
};

#endif /* CIRCLEPROCESSOR_H_ */
