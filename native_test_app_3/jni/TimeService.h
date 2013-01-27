/*
 * TimeService.h
 *
 *  Created on: 27.01.2013
 *      Author: pavel
 */

#ifndef TIMESERVICE_H_
#define TIMESERVICE_H_

#include <time.h>

#include "Types.hpp"

namespace smallarsdk {

class TimeService {
public:
	TimeService();
	virtual ~TimeService();

	void reset();
	void update();

	double now();
	float elapsed();

protected:
	float   _elapsed;
	double  _lastTime;
};

} /* namespace smallarsdk */
#endif /* TIMESERVICE_H_ */
