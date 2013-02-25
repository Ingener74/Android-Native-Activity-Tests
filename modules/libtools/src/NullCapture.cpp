/*
 * NullCapture.cpp
 *
 *  Created on: 18.02.2013
 *      Author: pavel
 */

#include "NullCapture.h"

NullCapture::NullCapture()
	: _outputImage(Mat(rows, cols, CV_8UC3, Scalar(190, 80, 20))),
	  _angle(0){
//	_outputImage = Mat(rows, cols, CV_8UC3 );
}

NullCapture::~NullCapture() {
}

void NullCapture::grab(){
	_outputImage = Mat(rows, cols, CV_8UC3, Scalar(r, b, g));
	double rad = min(rows/2, cols/2) * 0.8;
	circle( _outputImage,
			Point(cols/2, rows/2) + Point(rad * cos(_angle), rad * sin(_angle)),
			rad, Scalar(0, 190, 40), 6);
	_angle += 0.1;
}

Mat& NullCapture::getImage(){

//	static uchar r = 0, g = 0, b = 0;
//	if( ++r       >= 256 ) r = 0;
//	if( (g += 10) >= 256 ) g = 0;
//	if( (b *=  2) >= 256 ) b = 0;
//	circle(_outputImage, Point(50, 50), 40,
//			Scalar( (r+255)%255, (g+255)%255, (b+255)%255 ), 10);

	return _outputImage;
}
