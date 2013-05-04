/*
 * OGRETestApp.cpp
 *
 *  Created on: 04.05.2013
 *      Author: pavel
 */

#include "OGRETestApp.h"

namespace ogre_test {

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
	while(seci.hasMoreElements()){
		sectionName = seci.peekNextKey();
		ConfigFile::SettingsMultiMap* settings = seci.getNext();
		ConfigFile::SettingsMultiMap::iterator i;
		for( i = settings->begin(); i != settings->end(); ++i ){
			typeName = i->first;
			archName = i->second;
			ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, sectionName);
		}
	}

	if(_root->restoreConfig() || _root->showConfigDialog() ){
		_window = _root->initialise(true, "OGRE Test applicaion");
	}else{
		return false;
	}

	_sceneManager = _root->createSceneManager(ST_GENERIC);

	_camera = _sceneManager->createCamera("MainCamera");
	_camera->setPosition(0, 7, 3);
	_camera->lookAt(0, 0, 0);
	_camera->setNearClipDistance(0.1);

	Viewport* vp = _window->addViewport(_camera);
	vp->setBackgroundColour(ColourValue(0.1f, 0.3f, 0.1f, 1.f));

	_camera->setAspectRatio( vp->getActualWidth() / Real(vp->getActualHeight()) );

//	TextureManager::getSingleton().setDefaultNumMipmaps(5);

	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	/*
	 * Create Scene
	 */

//	/home/pavel/prj/Android-Native-Activity-Tests/data/apps/06_OGRE_Test/Kubelwagen/

	Entity* car = _sceneManager->createEntity("Car", "Kubelwagen.mesh");
	SceneNode* carNode = _sceneManager->getRootSceneNode()->createChildSceneNode();
	carNode->attachObject(car);
	carNode->rotate(Vector3(0, 1, 0), Radian(90));

	/*
	 * end Create Scene
	 */

	_sceneManager->setAmbientLight(ColourValue(0.5f, 0.5f, 0.5f));

	Light* l = _sceneManager->createLight("MainLight");
	l->setPosition(100, 100, 100);

	while(1){
		WindowEventUtilities::messagePump();
		if(_window->isClosed()){
			return false;
		}

		carNode->rotate(Vector3(1, 0, 0), Radian(0.007));

		if(!_root->renderOneFrame()){
			return false;
		}
	}

	return true;
}

} /* namespace ogre_test */
