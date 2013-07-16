/*
 * OGRETestApp.h
 *
 *  Created on: 04.05.2013
 *      Author: pavel
 */

#ifndef OGRETESTAPP_H_
#define OGRETESTAPP_H_

#include <OGRE/Ogre.h>

#include <OIS/OIS.h>

using namespace Ogre;

namespace ogre_test {

class SimpleMouseListener: public OIS::MouseListener {
public:
	SimpleMouseListener( Camera* camera ): _camera(camera), _radius(10), _rad1(0), _rad2(0){
	}
	virtual ~SimpleMouseListener() {
	}
	bool mouseMoved(const OIS::MouseEvent &arg);
	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

private:
	Camera* _camera;

	double _radius, _rad1, _rad2;
};

class SimpleKeyListener: public OIS::KeyListener {
public:
	SimpleKeyListener( SceneNode* sceneNode ){ _node = sceneNode; }
	virtual ~SimpleKeyListener() {
	}
	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
private:
	SceneNode* _node;
};

class SimpleFrameListener: public FrameListener {
public:
	SimpleFrameListener(OIS::Keyboard* keyboard, OIS::Mouse* mouse) :
			_keyboard(keyboard), _mouse(mouse) {
	}
	virtual ~SimpleFrameListener() {
	}

	bool frameStarted(const FrameEvent& evt);
	bool frameEnded(const FrameEvent& evt);

private:
	OIS::Keyboard* _keyboard;
	OIS::Mouse* _mouse;
};

class OGRETestApp {
public:
	OGRETestApp(String plugins, String resources);
	virtual ~OGRETestApp();

	bool run();

private:
	Root*                _root;

	Camera*              _camera;

	SceneManager*        _sceneManager;
	RenderWindow*        _window;
	Timer*               _timer;

	String               _pluginsConfig;
	String               _resourcesConfig;

	OIS::InputManager*   _inputManager;

	OIS::Mouse*          _mouse;
	SimpleMouseListener* _mouseListener;

	OIS::Keyboard*       _keyboard;
	SimpleKeyListener*   _keyboardListener;

	SimpleFrameListener* _frameListener;
};

} /* namespace ogre_test */
#endif /* OGRETESTAPP_H_ */
