/*
 * OpenCVCapture.cpp
 *
 *  Created on: 18.02.2013
 *      Author: pavel
 */

#include "OpenCVCapture.h"

OpenCVCapture::OpenCVCapture( int32_t cam, int32_t rows, int32_t cols ): _isError(false){
	LOGI_OCV("OpenCVCapture constructor begin");

	_cv = VideoCapture(CV_CAP_ANDROID + cam);
	if(_cv.isOpened()){
		LOGI_OCV("OpenCVCapture created");
		_cv.set(CV_CAP_PROP_FRAME_HEIGHT, rows);
		_cv.set(CV_CAP_PROP_FRAME_WIDTH,  cols);
	}else{
		_isError = true;
		LOGI_OCV("OpenCVCapture can't create");
	}

	LOGI_OCV("OpenCVCapture constructor end");
}

OpenCVCapture::~OpenCVCapture() {
	LOGI_OCV("OpenCVCapture destructor begin");
	_cv.release();
	LOGI_OCV("OpenCVCapture destructor end");
}

void OpenCVCapture::grab(){
	if(_cv.isOpened()){
		_cv >> _im;
		cvtColor(_im, _im, CV_RGB2BGR);
	}else{
		_isError = true;
	}
}

Mat OpenCVCapture::getImage() {
	return _im;
}

void OpenCVCapture::stop(){
	LOGI_OCV("stop begin");
	_cv.release();
	LOGI_OCV("stop end");
}

bool OpenCVCapture::dataReady(){
	return false;
}

void OpenCVCapture::dataReaded(){
}
