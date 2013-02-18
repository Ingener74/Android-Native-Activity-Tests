/*
 * OpenCVCapture.cpp
 *
 *  Created on: 18.02.2013
 *      Author: pavel
 */

#include "OpenCVCapture.h"

OpenCVCapture::OpenCVCapture( int32_t cam ) {
	LOGI_OCV("OpenCVCapture constructor begin");

	_cv = VideoCapture(CV_CAP_ANDROID + cam);
	if(_cv.isOpened()){
		LOGI_OCV("OpenCVCapture created");
		_cv.set(CV_CAP_PROP_FRAME_HEIGHT, rows);
		_cv.set(CV_CAP_PROP_FRAME_WIDTH,  cols);
	}else{
		LOGI_OCV("OpenCVCapture can't create");
	}

	LOGI_OCV("OpenCVCapture constructor end");
}

OpenCVCapture::~OpenCVCapture() {
	LOGI_OCV("OpenCVCapture destructor begin");
	_cv.release();
	LOGI_OCV("OpenCVCapture destructor end");
}

Mat& OpenCVCapture::getImage() {
	LOGI_OCV("OpenCVCapture getImage begin");
	if(_cv.isOpened()){
		_cv >> _im;
		cvtColor(_im, _im, CV_RGB2BGR);
	}
	LOGI_OCV("OpenCVCapture getImage end");
	return _im;
}
