/*
 * IApplication.h
 *
 *  Created on: 13.07.2013
 *      Author: pavel
 */

#ifndef IAPPLICATION_H_
#define IAPPLICATION_H_

namespace are{

namespace application{

class IApplication {
public:
	IApplication(){}
	virtual ~IApplication(){}

	virtual bool initialization() = 0;
	virtual bool run() = 0;
	virtual bool deinitialization() = 0;
};

}
}


#endif /* IAPPLICATION_H_ */
