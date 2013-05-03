

#ifndef __TinyOgre_h_
#define __TinyOgre_h_

#include <OGRE/OgreRoot.h>
#include <OGRE/OgreCamera.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreRenderWindow.h>

class TinyOgre
{
public:
    TinyOgre( Ogre::String pluginsConfig, Ogre::String resourcesConfig );
    virtual ~TinyOgre(void);
    bool go(void);
    Ogre::RenderWindow * getWindow(void) { return mWindow; }
    Ogre::Timer * getTimer(void) { return mTimer; }

protected:
    Ogre::Root *mRoot;
    Ogre::Camera* mCamera;
    Ogre::SceneManager* mSceneMgr;
    Ogre::RenderWindow* mWindow;
    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;
    Ogre::Timer *mTimer;
};

#endif // #ifndef __TinyOgre_h_
