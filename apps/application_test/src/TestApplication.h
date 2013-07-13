/*
 * TestApplication.h
 *
 *  Created on: 13.07.2013
 *      Author: pavel
 */

#ifndef TESTAPPLICATION_H_
#define TESTAPPLICATION_H_

#include <IApplication.h>

class TestApplication : public are::application::IApplication {
public:
	TestApplication();
	virtual ~TestApplication();

	virtual bool initialization();
	virtual bool run();
	virtual bool deinitialization();
};

#endif /* TESTAPPLICATION_H_ */
