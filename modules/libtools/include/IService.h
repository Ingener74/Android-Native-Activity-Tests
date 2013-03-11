/*
 * IService.h
 *
 *  Created on: 26.02.2013
 *      Author: pavel
 */

#ifndef ISERVICE_H_
#define ISERVICE_H_

class IService {
public:
	IService(){}
	virtual ~IService(){}

	virtual bool isError() = 0;
	virtual void stop() = 0;
};

#endif /* ISERVICE_H_ */
