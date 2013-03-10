/*
 * NativeWindowGraphicsService.cpp
 *
 *  Created on: 18.02.2013
 *      Author: pavel
 */

#include "NativeWindowGraphicsService.h"

NativeWindowGraphicsService::NativeWindowGraphicsService(
		ICaptureService* captureService ): _cs(captureService){

}

NativeWindowGraphicsService::~NativeWindowGraphicsService() {
}

IGraphicsService::STATUS NativeWindowGraphicsService::init(
		android_app* application) {

	_application = application;

	LOGI_NWGS("native window init begin");

	_outImage = Mat(480, 640, CV_8UC3, Scalar(250, 120, 20));
	LOGI_NWGS("native window outim: %d x %d", _outImage.rows, _outImage.cols);

//	vc = VideoCapture(CV_CAP_ANDROID + 0);
//	if(vc.isOpened()){
//		vc.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
//		vc.set(CV_CAP_PROP_FRAME_WIDTH, 640);
//	}

	ANativeWindow* nw = application->window;
	LOGI_NWGS("native window set buff geom start = %d", nw);

	int32_t anw_sbg = ANativeWindow_setBuffersGeometry(application->window, 0, 0, WINDOW_FORMAT_RGBX_8888);

	LOGI_NWGS("native window set buff geom = %d", anw_sbg);

	LOGI_NWGS("native window init get buffer");

	if (ANativeWindow_lock(_application->window, &_windowBuffer, 0) >= 0) {
		ANativeWindow_unlockAndPost(_application->window);

		LOGI_NWGS("wb.w = %d", _windowBuffer.width);
		LOGI_NWGS("wb.h = %d", _windowBuffer.height);
		LOGI_NWGS("wb.s = %d", _windowBuffer.stride);

	} else {
		return IGraphicsService::STATUS_ERROR;
	}

	LOGI_NWGS("native window init end");
	return IGraphicsService::STATUS_OK;
}

void NativeWindowGraphicsService::deinit() {
}

void NativeWindowGraphicsService::draw() {

	LOGI_NWGS("native window draw begin");

//	vc >> _outImage;
	_outImage = _cs->getImage();

	ANativeWindow_lock(_application->window, &_windowBuffer, 0);
	if(!_outImage.empty()){
		LOGI_NWGS("outImage is not empty");
		register uint32_t* p = (uint32_t*)_windowBuffer.bits;
		register uchar*    cb = (uchar*)_outImage.data;

		int32_t w = _windowBuffer.stride;

		if(p){
			for( int32_t i = 0; i < _outImage.rows; ++i ){
				for( int32_t j = 0; j < _outImage.cols; ++j ){

					uint32_t cl = 0 +
							(*(cb + i * _outImage.step[0] + j*_outImage.step[1] + 0) << 16) +
							(*(cb + i * _outImage.step[0] + j*_outImage.step[1] + 1) << 8 ) +
							(*(cb + i * _outImage.step[0] + j*_outImage.step[1] + 2)      );

					*(p + i*w + j) = cl;
				}
			}
		}
	}else{
		LOGI_NWGS("native window outImage is empty");
	}
	ANativeWindow_unlockAndPost(_application->window);

	LOGI_NWGS("native window draw end");
}
