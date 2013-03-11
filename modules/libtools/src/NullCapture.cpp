/*
 * NullCapture.cpp
 *
 *  Created on: 18.02.2013
 *      Author: pavel
 */

#include "NullCapture.h"

NullCapture::NullCapture(): _angle(0), _stop(false) {
//	_im = Mat(h, w, CV_8UC4, Scalar(r, g, b, 255));
	_im = Mat(h, w, CV_8UC3, Scalar(r, g, b));
}

NullCapture::~NullCapture() {
}

void NullCapture::grab(){

	if(!_stop){
//		_im = Mat(h, w, CV_8UC4, Scalar(0, 90, 30, 255));
		_im = Mat(h, w, CV_8UC3, Scalar(0, 90, 30));

		int32_t rad = int32_t( 0.8 * min(h, w) / 2.0 );

		circle(_im,
				Point(w/2, h/2) + Point(rad*cos(_angle), rad*sin(_angle)),
				int32_t(rad * 0.1), Scalar(255, 0, 0), 6);

		_angle += 0.1;

		usleep(simulatedDelay * 1000);
	}
}

Mat NullCapture::getImage(){
	return _im;
}

void NullCapture::stop(){
	_stop = true;
}

bool NullCapture::dataReady(){
	return false;
}

void NullCapture::dataReaded(){
}
