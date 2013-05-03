
#include "TinyOgre.h"

#include <OGRE/OgreLogManager.h>
#include <OGRE/OgreViewport.h>
#include <OGRE/OgreConfigFile.h>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreWindowEventUtilities.h>

//-------------------------------------------------------------------------------------
TinyOgre::TinyOgre( Ogre::String pluginsConfig, Ogre::String resourcesConfig )
    : mRoot(0),
    mCamera(0),
    mSceneMgr(0),
    mWindow(0),
    mResourcesCfg(resourcesConfig),
    mPluginsCfg(pluginsConfig)
{
	mTimer = OGRE_NEW Ogre::Timer();
	mTimer->reset();
}
//-------------------------------------------------------------------------------------
TinyOgre::~TinyOgre(void)
{
    delete mRoot;
}

bool TinyOgre::go(void)
{
    // construct Ogre::Root
    mRoot = new Ogre::Root(mPluginsCfg);

//-------------------------------------------------------------------------------------
    // setup resources
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
//-------------------------------------------------------------------------------------
    // configure
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    if(mRoot->restoreConfig() || mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        mWindow = mRoot->initialise(true, "TinyOgre Render Window");
    }
    else
    {
        return false;
    }
//-------------------------------------------------------------------------------------
    // choose scenemanager
    // Get the SceneManager, in this case a generic one
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
//-------------------------------------------------------------------------------------
    // create camera
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(0, 120, 200));
    // Look back along -Z
//    mCamera->lookAt(Ogre::Vector3(0,0,-300));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);

//-------------------------------------------------------------------------------------
    // create viewports
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
//-------------------------------------------------------------------------------------
    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
//-------------------------------------------------------------------------------------
    // Create any resource listeners (for loading screens)
    //createResourceListener();
//-------------------------------------------------------------------------------------
    // load resources
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
//-------------------------------------------------------------------------------------
    // Create the scene
    Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
    Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    headNode->attachObject(ogreHead);

    Ogre::Entity* ogreHead2 = mSceneMgr->createEntity("Head2", "ogrehead.mesh");


    Ogre::SceneNode* headNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    headNode2->attachObject(ogreHead2);
    headNode2->translate(50, 0, 0);
    headNode2->rotate(Ogre::Vector3(0, 1, 0), Ogre::Radian(45));



    // Set ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    // Create a light
    Ogre::Light* l = mSceneMgr->createLight("MainLight");
    l->setPosition(20,80,50);
//-------------------------------------------------------------------------------------

    while(true)
    {
        // Pump window messages for nice behaviour
        Ogre::WindowEventUtilities::messagePump();

        if(mWindow->isClosed())
        {
            return false;
        }

        // Render a frame
        if(!mRoot->renderOneFrame()) return false;
    }

    // We should never be able to reach this corner
    // but return true to calm down our compiler
    return true;
}

int main(int argc, char *argv[])
{
	if(argc == 3){
		TinyOgre app(argv[1], argv[2]);
		try {
			app.go();
		} catch( Ogre::Exception& e ) {
			std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
		}
	}else{
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

