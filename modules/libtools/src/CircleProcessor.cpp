/*
 * CircleProcessor.cpp
 *
 *  Created on: 18.02.2013
 *      Author: pavel
 */

#include "CircleProcessor.h"

#include <opencv2/highgui/highgui.hpp>

CircleProcessor::CircleProcessor( ICaptureService* captureService, IGraphicsService* graphService )
	: IProcessor(captureService, graphService) {
}

CircleProcessor::~CircleProcessor() {
}

void CircleProcessor::process(){

	if( _gs && _cs ){
		LOGI("CircleProcessor", "process begin");

		_cs->grab();

		Mat im = _cs->getImage();

		int32_t rad = int32_t( min(im.rows/2, im.cols/2) * 0.8 );
		circle(im, Point(im.cols/2, im.rows/2), rad, CV_RGB(140, 160, 30), 4);

		_gs->setImage(im);

		LOGI("CircleProcessor", "process end");
	}
}
