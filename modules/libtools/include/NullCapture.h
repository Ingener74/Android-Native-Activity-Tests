/*
 * NullCapture.h
 *
 *  Created on: 18.02.2013
 *      Author: pavel
 */

#ifndef NULLCAPTURE_H_
#define NULLCAPTURE_H_

#include "ICaptureService.h"

class NullCapture: public ICaptureService {
public:
	NullCapture();
	virtual ~NullCapture();

	Mat& getImage();

protected:
	static const int32_t rows = 480, cols = 640;
	Mat _outputImage;
};

#endif /* NULLCAPTURE_H_ */
