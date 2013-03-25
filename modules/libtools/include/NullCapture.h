/*
 * NullCapture.h
 *
 *  Created on: 18.02.2013
 *      Author: pavel
 */

#ifndef NULLCAPTURE_H_
#define NULLCAPTURE_H_

#include <unistd.h>

#include "ICaptureService.h"

static const int32_t h = 480, w = 640;

class NullCapture: public ICaptureService {
public:
	static const uchar r = 0, g = 90, b = 30;
	static const int32_t simulatedDelay = 1000 /*ms in sec*/ / 60 /*fps*/;

	NullCapture();
	virtual ~NullCapture();

	void grab();
	Mat getImage();

	void stop();

	bool isError() { return false; }

	bool dataReady();
	void dataReaded();

protected:
	double _angle;
	bool   _stop;
	Mat    _im;
};

#endif /* NULLCAPTURE_H_ */
