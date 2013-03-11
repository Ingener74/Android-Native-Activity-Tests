/*
 * ICaptureService.h
 *
 *  Created on: 18.02.2013
 *      Author: pavel
 */

#ifndef ICAPTURESERVICE_H_
#define ICAPTURESERVICE_H_

#include <opencv2/core/core.hpp>

#include "IService.h"

using namespace cv;

class ICaptureService: public IService {
public:
	virtual ~ICaptureService(){}

	virtual void grab() = 0;

	virtual Mat getImage() = 0;
	virtual void dataReaded() = 0;

	virtual bool dataReady() = 0;
};

#endif /* ICAPTURESERVICE_H_ */
