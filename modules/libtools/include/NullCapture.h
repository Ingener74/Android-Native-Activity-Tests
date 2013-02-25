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

	void grab();
	Mat& getImage();

protected:
	Mat _outputImage;
	double _angle;
	static const int32_t rows = 480, cols = 640;
	static const uchar r = 190, g = 100, b = 20;
	static const int32_t simulatedDelay = 1000 * 16;
};

#endif /* NULLCAPTURE_H_ */
