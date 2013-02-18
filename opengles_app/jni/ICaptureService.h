/*
 * ICaptureService.h
 *
 *  Created on: 18.02.2013
 *      Author: pavel
 */

#ifndef ICAPTURESERVICE_H_
#define ICAPTURESERVICE_H_

#include <opencv2/core/core.hpp>

using namespace cv;

class ICaptureService {
public:
	virtual ~ICaptureService(){}

	virtual Mat& getImage() = 0;
};

#endif /* ICAPTURESERVICE_H_ */
