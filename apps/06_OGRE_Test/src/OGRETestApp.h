/*
 * OGRETestApp.h
 *
 *  Created on: 04.05.2013
 *      Author: pavel
 */

#ifndef OGRETESTAPP_H_
#define OGRETESTAPP_H_

#include <OGRE/Ogre.h>

using namespace Ogre;

namespace ogre_test {

class OGRETestApp {
public:
	OGRETestApp( String plugins, String resources );
	virtual ~OGRETestApp();

	bool run();

private:
	Root*          _root;
	Camera*        _camera;
	SceneManager*  _sceneManager;
	RenderWindow*  _window;
	Timer*         _timer;

	String         _pluginsConfig;
	String         _resourcesConfig;
};

} /* namespace ogre_test */
#endif /* OGRETESTAPP_H_ */
