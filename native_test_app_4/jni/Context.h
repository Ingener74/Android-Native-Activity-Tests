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

class GraphicsService;
class TimeService;

struct Context {
	GraphicsService* graphicsService;
	TimeService*     timeService;
};

} /* namespace smallarsdk */
#endif /* CONTEXT_H_ */
