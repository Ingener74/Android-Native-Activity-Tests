/*
 * NullCapture.cpp
 *
 *  Created on: 18.02.2013
 *      Author: pavel
 */

#include "NullCapture.h"

NullCapture::NullCapture() {
	_outputImage = Mat(rows, cols, CV_8UC3 );
}

NullCapture::~NullCapture() {
}

Mat& NullCapture::getImage(){
	static uchar r = 0, g = 0, b = 0;
	if( ++r       >= 256 ) r = 0;
	if( (g += 10) >= 256 ) g = 0;
	if( (b *=  2) >= 256 ) b = 0;

	_outputImage = Mat(rows, cols, CV_8UC3, Scalar(r, b, g));

	circle(_outputImage, Point(50, 50), 40,
			Scalar( (r+255)%255, (g+255)%255, (b+255)%255 ), 10);

	return _outputImage;
}
