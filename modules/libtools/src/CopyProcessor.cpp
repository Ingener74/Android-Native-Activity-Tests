/*
 * CopyProcessor.cpp
 *
 *  Created on: 10.03.2013
 *      Author: pavel
 */

#include "CopyProcessor.h"

CopyProcessor::CopyProcessor( ICaptureService* cs, IGraphicsService* gs ):
	IProcessor(cs, gs) {
}

CopyProcessor::~CopyProcessor() {
}

void CopyProcessor::process(){
	if(_cs && _gs){
		_cs->grab();

		Mat im = _cs->getImage();
		circle(im, Point(20, 20), 10, Scalar(0,255,0), -1);
		_gs->setImage(im);
	}
}
