/*
 * OpenCVCapture.h
 *
 *  Created on: Feb 18, 2013
 *      Author: ingener
 */

#ifndef OPENCVCAPTURE_H_
#define OPENCVCAPTURE_H_

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "ICaptureService.h"

#include "tools.h"

#define LOGI_OCV(...){ LOGI("OpenCVCapture", __VA_ARGS__); }

class OpenCVCapture: public ICaptureService{
public:
	OpenCVCapture( int32_t cam = 0 );
	virtual ~OpenCVCapture();

	virtual Mat& getImage();
protected:
	static const int32_t rows = 480, cols = 640;

	VideoCapture _cv;
	Mat          _im;
};


#endif /* OPENCVCAPTURE_H_ */
