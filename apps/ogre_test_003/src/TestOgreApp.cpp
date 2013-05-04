/*
 * TestOgreApp.cpp
 *
 *  Created on: 03.05.2013
 *      Author: pavel
 */

#include <stdint.h>

#include "TestOgreApp.h"

namespace ogre_test_003 {

TestOgreApp::TestOgreApp(Ogre::String pluginConfig, Ogre::String resourceConfig) :
		_root(NULL), _camera(NULL), _sceneMgr(NULL), _window(NULL), _timer(
				NULL), _pluginConfig(pluginConfig), _resourceConfig(
				resourceConfig) {

	_timer = OGRE_NEW Ogre::Timer();
	_timer->reset();
}

TestOgreApp::~TestOgreApp() {
}

bool TestOgreApp::init() {

	// create root
	_root = new Ogre::Root(_pluginConfig);

	// load resource
	Ogre::ConfigFile cf;
	cf.load(_resourceConfig);

	// view all section in config
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String sectionName, typeName, archName;
	while (seci.hasMoreElements()) {
		sectionName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i) {
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
					archName, typeName, sectionName);
		}
	}

	// configure
	if (_root->restoreConfig() || _root->showConfigDialog()) {
		_window = _root->initialise(true, "ogre test 003 render window");
	} else {
		return false;
	}

	// choose scene manager
	_sceneMgr = _root->createSceneManager(Ogre::ST_GENERIC);

	// create camera
	_camera = _sceneMgr->createCamera("MainCamera");

	_camera->setPosition(0, 300, 300);
	_camera->lookAt(0, 0, 0);
	_camera->setNearClipDistance(5);

	// create viewport
	Ogre::Viewport* vp = _window->addViewport(_camera);
	vp->setBackgroundColour(Ogre::ColourValue(0.1f, 0.4f, 0.2f, 1.f));

	_camera->setAspectRatio(
			Ogre::Real(vp->getActualWidth())
					/ Ogre::Real(vp->getActualHeight()));

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	// load resource
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	// create scene
	Ogre::Entity* ogreHead = _sceneMgr->createEntity("Head", "ogrehead.mesh");
	Ogre::SceneNode* headNode =
			_sceneMgr->getRootSceneNode()->createChildSceneNode();
	headNode->attachObject(ogreHead);

//	Ogre::Entity* robotEn = _sceneMgr->createEntity("Robot", "spine.mesh");
//	Ogre::SceneNode* robotNode = _sceneMgr->getRootSceneNode()->createChildSceneNode();
//	robotNode->attachObject(robotEn);

	/*
	 * creating a line
	 */
	Ogre::ManualObject* line001 = _sceneMgr->createManualObject("line001");

	const double x1 = 0, x2 = 100;
	const uint32_t count = 200;

	line001->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
	for( uint32_t i = 0; i < count; ++i ){

		double x = i / double(count);
		double sin_x = sin( 2 * M_PI * x );

		line001->position( 200 * x, 100 * sin_x, 0);
	}
	line001->end();
	Ogre::SceneNode* lineNode = _sceneMgr->getRootSceneNode()->createChildSceneNode();
	lineNode->attachObject(line001);

	// set light
	_sceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.6f));

	Ogre::Light* l = _sceneMgr->createLight("mainLight");
	l->setPosition(20, 80, 100);

	while(true){
		Ogre::WindowEventUtilities::messagePump();
		if( _window->isClosed() ){
			return false;
		}
		headNode->rotate(Ogre::Vector3(0, 1, 0), Ogre::Radian(0.05));

//		robotNode->translate(0.1, 0, 0);

		if( !_root->renderOneFrame() ){
			return false;
		}
	}
	return true;
}

} /* namespace ogre_test_003 */

