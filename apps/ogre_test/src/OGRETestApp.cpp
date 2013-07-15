/*
 * OGRETestApp.cpp
 *
 *  Created on: 04.05.2013
 *      Author: pavel
 */
#include <stdint.h>
#include <string>
#include <iostream>

#include "OGRETestApp.h"

namespace ogre_test {

/*
 * Mouse Listener
 */
bool SimpleMouseListener::mouseMoved(const OIS::MouseEvent& arg) {
	return true;
}
bool SimpleMouseListener::mousePressed(const OIS::MouseEvent& arg,
		OIS::MouseButtonID id) {
	std::cout << "mouse pressed" << std::endl;
	return true;
}
bool SimpleMouseListener::mouseReleased(const OIS::MouseEvent& arg,
		OIS::MouseButtonID id) {
	std::cout << "mouse released" << std::endl;
	return true;
}

/*
 * Key Listener
 */
bool SimpleKeyListener::keyPressed(const OIS::KeyEvent& arg) {
	if(arg.key == OIS::KC_LEFT){
		_node->translate(1, 0, 0);
	}
	if(arg.key == OIS::KC_RIGHT){
		_node->translate(-1, 0, 0);
	}
	return true;
}
bool SimpleKeyListener::keyReleased(const OIS::KeyEvent& arg) {
	return true;
}

/*
 * Frame Listener
 */
bool SimpleFrameListener::frameStarted(const FrameEvent& evt) {
	_keyboard->capture();
	_mouse->capture();

	if (_keyboard->isKeyDown(OIS::KC_ESCAPE)) {
		return false;
	}

	return true;
}
bool SimpleFrameListener::frameEnded(const FrameEvent& evt) {
	return true;
}

OGRETestApp::OGRETestApp(String plugins, String resources) :
		_root(NULL), _camera(NULL), _sceneManager(NULL), _window(NULL), _timer(
				NULL), _pluginsConfig(plugins), _resourcesConfig(resources) {

	// timer
}

OGRETestApp::~OGRETestApp() {
}

bool OGRETestApp::run() {

	_root = new Root(_pluginsConfig);

	ConfigFile cf;
	cf.load(_resourcesConfig);

	ConfigFile::SectionIterator seci = cf.getSectionIterator();

	String sectionName, typeName, archName;
	while (seci.hasMoreElements()) {
		sectionName = seci.peekNextKey();
		ConfigFile::SettingsMultiMap* settings = seci.getNext();
		ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i) {
			typeName = i->first;
			archName = i->second;
			ResourceGroupManager::getSingleton().addResourceLocation(archName,
					typeName, sectionName);
		}
	}

	if (_root->restoreConfig() || _root->showConfigDialog()) {
		_window = _root->initialise(true, "OGRE Test applicaion");

	} else {
		return false;
	}

	_sceneManager = _root->createSceneManager(ST_GENERIC);

	_camera = _sceneManager->createCamera("MainCamera");
	_camera->setPosition(0, 7, -7);
	_camera->lookAt(0, 0, 0);
	_camera->setNearClipDistance(0.1);
	_camera->setFarClipDistance(1000.f);

	Viewport* vp = _window->addViewport(_camera);
	vp->setBackgroundColour(ColourValue(0.1f, 0.3f, 0.1f, 1.f));

	_camera->setAspectRatio(vp->getActualWidth() / Real(vp->getActualHeight()));

	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	/*
	 * Create Scene
	 */
	Entity* car = _sceneManager->createEntity("Car", "Kubelwagen.mesh");
	SceneNode* carNode =
			_sceneManager->getRootSceneNode()->createChildSceneNode();
	carNode->attachObject(car);

	/*
	 * end Create Scene
	 */

	_sceneManager->setAmbientLight(ColourValue(0.5f, 0.5f, 0.5f));

	Light* l = _sceneManager->createLight("MainLight");
	l->setPosition(100, 100, 100);

	/*
	 * set listeners
	 */
	OIS::ParamList pl;
	size_t windowHandler = 0;
	std::stringstream windowHndString;

	_window->getCustomAttribute("WINDOW", &windowHandler);

	windowHndString << windowHandler;

	pl.insert(std::make_pair(std::string("WINDOW"), windowHndString.str()));

	_inputManager = OIS::InputManager::createInputSystem(pl);
	_mouse = static_cast<OIS::Mouse*>(_inputManager->createInputObject(
			OIS::OISMouse, true));
	_keyboard = static_cast<OIS::Keyboard*>(_inputManager->createInputObject(
			OIS::OISKeyboard, true));

	unsigned int width, height, depth;
	int top, left;
	_window->getMetrics(width, height, depth, left, top);

	const OIS::MouseState& ms = _mouse->getMouseState();
	ms.height = height;
	ms.width = width;

	_mouseListener = new SimpleMouseListener(_camera);
	_mouse->setEventCallback(_mouseListener);

	_keyboardListener = new SimpleKeyListener(carNode);
	_keyboard->setEventCallback(_keyboardListener);

	_frameListener = new SimpleFrameListener(_keyboard, _mouse);
	_root->addFrameListener(_frameListener);
	/*
	 * end set listeners
	 */

	_root->startRendering();

	/*
	 * clean
	 */

	_inputManager->destroyInputObject(_mouse);
	_mouse = NULL;
	_inputManager->destroyInputObject(_keyboard);
	_keyboard = NULL;
	OIS::InputManager::destroyInputSystem(_inputManager);
	_inputManager = NULL;

	delete _frameListener;
	delete _keyboardListener;
	delete _mouseListener;

	delete _root;

	return true;
}

} /* namespace ogre_test */
