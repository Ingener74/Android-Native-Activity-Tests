/*
 * OpenCVCapture.h
 *
 *  Created on: 18.02.2013
 *      Author: pavel
 */

#ifndef OPENCVCAPTURE_H_
#define OPENCVCAPTURE_H_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "ICaptureService.h"
#include "tools.h"

#define LOGI_OCV(...){ LOGI("OpenCVCapture", __VA_ARGS__); }

class OpenCVCapture: public ICaptureService {
public:
	static const int32_t defaultRows = 480, defaultCols = 640,
		defaultCamera = 0;

	OpenCVCapture( int32_t cam = defaultCamera, int32_t rows = defaultRows,
			int32_t cols = defaultCols);
	virtual ~OpenCVCapture();

	void grab();
	Mat getImage();

	void stop();

	bool isError(){
		return _isError;
	}

	bool dataReady();
	void dataReaded();

protected:
	VideoCapture  _cv;
	Mat           _im;

	bool          _isError;
};

#endif /* OPENCVCAPTURE_H_ */
