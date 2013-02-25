/*
 * IGraphicsService.h
 *
 *  Created on: Feb 18, 2013
 *      Author: ingener
 */

#ifndef IGRAPHICSSERVICE_H_
#define IGRAPHICSSERVICE_H_

#include <opencv2/core/core.hpp>
#include <android_native_app_glue.h>

namespace opengles_test {

using namespace cv;

class IGraphicsService {
public:
	typedef enum{
		STATUS_ERROR,
		STATUS_OK
	} STATUS ;

	IGraphicsService();
	virtual ~IGraphicsService();

	virtual STATUS init( android_app* application ) = 0;
	virtual void deinit() = 0;

	virtual void draw() = 0;

	virtual void setImage( const Mat& image ) = 0;

protected:
	android_app* _application;
};

} /* namespace opengles_test */
#endif /* IGRAPHICSSERVICE_H_ */
