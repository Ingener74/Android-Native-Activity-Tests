/*
 * Types.hpp
 *
 *  Created on: 25.01.2013
 *      Author: pavel
 */

#ifndef TYPES_HPP_
#define TYPES_HPP_

#include <stdint.h>

typedef int32_t status;

const status STATUS_OK = 0;
const status STATUS_KO = -1;
const status STATUS_EXIT = -2;

struct Location{
	Location(): _x(0), _y(0){
	}
	void setPosition( float x, float y ){
		_x = x; _y = y;
	}
	void translate( float dx, float dy ){
		_x += dx; _y += dy;
	}

	float _x, _y;
};

#endif /* TYPES_HPP_ */
