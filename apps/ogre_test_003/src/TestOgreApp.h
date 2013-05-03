/*
 * TestOgreApp.h
 *
 *  Created on: 03.05.2013
 *      Author: pavel
 */

#ifndef TESTOGREAPP_H_
#define TESTOGREAPP_H_

#include <OGRE/Ogre.h>

namespace ogre_test_003 {

class TestOgreApp {
public:
	TestOgreApp(Ogre::String pluginConfig, Ogre::String resourceConfig);
	virtual ~TestOgreApp();

	bool init();

	Ogre::Root* getRoot() {
		return _root;
	}
	Ogre::RenderWindow* getWindow() {
		return _window;
	}
	Ogre::Timer* getTimer() {
		return _timer;
	}

private:
	Ogre::Root* _root;
	Ogre::Camera* _camera;
	Ogre::SceneManager* _sceneMgr;
	Ogre::RenderWindow* _window;
	Ogre::Timer* _timer;

	Ogre::String _pluginConfig;
	Ogre::String _resourceConfig;
};

} /* namespace ogre_test_003 */
#endif /* TESTOGREAPP_H_ */
