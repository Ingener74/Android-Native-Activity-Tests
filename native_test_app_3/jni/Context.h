/*
 * Context.h
 *
 *  Created on: 27.01.2013
 *      Author: pavel
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_

#include "Types.hpp"

namespace smallarsdk {

class TimeService;

struct Context {
	TimeService* timeService;
};

} /* namespace smallarsdk */
#endif /* CONTEXT_H_ */
