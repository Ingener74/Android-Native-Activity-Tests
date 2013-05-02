
#include <iostream>
#include <OGRE/Ogre.h>

#include <OIS/OIS.h>

const char* caption =
		"OGRE Test application"
		;
const char* usage =
		"Usage: ./ogre_test_001 <path-to-resources.cfg>"
		;
using namespace Ogre;

int main( int argc, char* argv[] ){

	if(argc == 2){
		std::cout << caption << std::endl;
		Root* root = new Root;

		ConfigFile cf;
		cf.load(argv[1]);

		ConfigFile::SectionIterator seci = cf.getSectionIterator();

		String secName, typeName, archName;

		while(seci.hasMoreElements()){
			secName = seci.peekNextKey();

			ConfigFile::SettingsMultiMap *settings = seci.getNext();
			ConfigFile::SettingsMultiMap::iterator i;
			for( i = settings->begin(); i != settings->end(); ++i ){
				typeName = i->first;
				archName = i->second;
				ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
			}
		}

		if(root){
			if(root->showConfigDialog()){
				RenderWindow* window = root->initialise(true, "ogre test 001");

				ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

				SceneManager* sceneMgr = root->createSceneManager(ST_GENERIC);

				Camera* camera = sceneMgr->createCamera("simpleCamera");

				Viewport* viewPort = window->addViewport(camera);

//				OIS::ParamList pl;
//				size_t windowHnd = 0;

				root->startRendering();

			}else{
				delete root;
				std::cerr << "error in root" << std::endl; exit(EXIT_FAILURE);
			}
		}else{
			std::cout << "root is NULL" << std::endl;
		}

	}else{
		std::cerr << usage << std::endl; exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
