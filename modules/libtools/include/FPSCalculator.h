/*
 * FPSCalculator.h
 *
 *  Created on: 09.03.2013
 *      Author: pavel
 */

#ifndef FPSCALCULATOR_H_
#define FPSCALCULATOR_H_

#include <time.h>
#include <stdio.h>

class FPSCalculator {
public:
	FPSCalculator();
	virtual ~FPSCalculator();

	void start();
	void stop();

	double      getFPS();
	const char* getFPS( const char* name );

private:
	/*
	 * constants
	 */
	const static uint16_t _maxFPSBuffer = 256;
	const static double   _ms_in_sec = 1000.0;

	/*
	 * data
	 */
	clock_t _start;
	double  _fps;
	char    _fps_buffer[_maxFPSBuffer];
};

#endif /* FPSCALCULATOR_H_ */
