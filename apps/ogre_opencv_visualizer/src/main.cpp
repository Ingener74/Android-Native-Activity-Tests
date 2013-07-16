/*
 * main.cpp
 *
 *  Created on: 15.07.2013
 *      Author: pavel
 */

#include <string>
#include <iostream>
#include <vector>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <opencv2/opencv.hpp>

#include <OGRE/Ogre.h>
#include <OIS/OIS.h>

class OOV_KeyListener: public OIS::KeyListener{
public:
	OOV_KeyListener(){
	}
	virtual ~OOV_KeyListener(){}

	virtual bool keyPressed(const OIS::KeyEvent& arg){
		return true;
	}
	virtual bool keyReleased(const OIS::KeyEvent& arg){
		return true;
	}
};

class OOV_WindowListener: public Ogre::WindowEventListener {
public:
	OOV_WindowListener(): _exit(false){
	}
	virtual ~OOV_WindowListener(){}

	virtual void windowMoved(Ogre::RenderWindow* rw){
	}
	virtual void windowResized(Ogre::RenderWindow* rw){
	}
	virtual bool windowClosing(Ogre::RenderWindow* rw){
		_exit = true;
		return false;
	}
	virtual void windowClosed(Ogre::RenderWindow* rw){
	}
	virtual void windowFocusChange(Ogre::RenderWindow* rw){
	}
	bool isExit(){
		return _exit;
	}
private:
	bool _exit;
};

class OOV_FrameListener: public Ogre::FrameListener{
public:
	OOV_FrameListener( OIS::Keyboard* keyboard,
			cv::VideoCapture* vc,
			Ogre::TexturePtr screenTex,
			OOV_WindowListener* windowListener ):
				_keyboard(keyboard),
				_vc(vc),
				_screenTex(screenTex),
				_windowListener(windowListener){
	}
	virtual ~OOV_FrameListener(){}
	bool frameStarted(const Ogre::FrameEvent& event){
		_keyboard->capture();
		if(_keyboard->isKeyDown(OIS::KC_ESCAPE)){
			return false;
		}

		if(_windowListener->isExit()){
			return false;
		}

		if(_vc){
			cv::Mat im;

			if(_vc->grab()){
				if(_vc->retrieve(im)){

					Ogre::HardwarePixelBufferSharedPtr pixelBuffer = _screenTex->getBuffer();

					pixelBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD);
					const Ogre::PixelBox& pixelBox = pixelBuffer->getCurrentLock();

					uint8_t* dst = static_cast<uint8_t*>(pixelBox.data);
					uint8_t* src = im.data;

					for( size_t i = 0; i < im.rows; ++i ){
						for( size_t j = 0; j < im.cols; ++j ){
							*dst++ = *src++;
							*dst++ = *src++;
							*dst++ = *src++;
							*dst++ = 255;
						}
					}

					pixelBuffer->unlock();
				}
			}
		}

		return true;
	}
	bool frameEnded(const Ogre::FrameEvent& event){
		return true;
	}
private:
	OIS::Keyboard* _keyboard;
	cv::VideoCapture* _vc;

	Ogre::TexturePtr _screenTex;

	OOV_WindowListener* _windowListener;
};

int main( int argc, char* argv[] ){

	po::options_description desc("General description");
	desc.add_options()
			("help,h", "Show help")
			("mode,m", po::value<std::string>()->default_value("play"), "Set working mode")
			("source,s", po::value<std::string>()->default_value("cam"), "Video source")
			("cam,c", po::value<uint8_t>()->default_value(0), "Camera number")
			("file,f", po::value<std::string>(), "Input video file")
			("resolution,r", po::value<std::vector<int> >()->multitoken(), "Camera resolution")
			("plugins,P", po::value<std::string>(), "plugins.cfg file")
			("resources,R", po::value<std::string>(), "resources.cfg file")
			;
	po::variables_map vm;

	try{
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);
	}catch(...){
		desc.print(std::cerr);
		std::cerr << "throw then argument parsing" << std::endl;
		return 1;
	}

	if(vm.count("help")){
		desc.print(std::cout);
		std::cout <<
				"Usage: " << std::endl <<
				"./apps/ogre_opencv_visualizer/oov -P data/apps/ogre_test/plugins.cfg -R data/apps/ogre_test/resources.cfg" << std::endl <<
				"./apps/ogre_opencv_visualizer/oov -P data/apps/ogre_test/plugins.cfg -R data/apps/ogre_test/resources.cfg -r 720 960" << std::endl;
		return 0;
	}

	size_t camR = 0, camC = 0;

	cv::VideoCapture vc;
	if(vm["mode"].as<std::string>() == "play"){
		if(vm["source"].as<std::string>() == "cam"){
			vc = cv::VideoCapture(vm["cam"].as<uint8_t>());
			if(vm.count("resolution")){
				vc.set(CV_CAP_PROP_FRAME_HEIGHT, vm["resolution"].as<std::vector<int> >()[0]);
				vc.set(CV_CAP_PROP_FRAME_WIDTH,  vm["resolution"].as<std::vector<int> >()[1]);
			}
		}else if(vm["source"].as<std::string>() == "file"){
			if(!vm.count("file")){
				desc.print(std::cerr);
				std::cerr << "no source file" << std::endl;
				return 1;
			}
			vc = cv::VideoCapture(vm["file"].as<std::string>());
		}else{
			desc.print(std::cerr);
			return 1;
		}
		camR = vc.get(CV_CAP_PROP_FRAME_HEIGHT);
		camC = vc.get(CV_CAP_PROP_FRAME_WIDTH);
	}else if(vm["mode"].as<std::string>() == "record"){
	}

	Ogre::Root*         _root = 0;
	Ogre::Camera*       _camera = 0;
	Ogre::SceneManager* _sceneManager = 0;
	Ogre::RenderWindow* _renderWindow = 0;
	Ogre::Timer*        _timer  = 0;

	OIS::InputManager*  _inputManager = 0;
	OIS::Keyboard*      _keyboard = 0;
	OOV_KeyListener*    _keyboardListener = 0;

	OOV_WindowListener* _windowEventListener = 0;

	OOV_FrameListener*  _frameListener = 0;

	if(!vm.count("plugins")){
		desc.print(std::cerr);
		std::cerr << "plugins is empty" << std::endl;
		return 1;
	}
	if(!vm.count("resources")){
		desc.print(std::cerr);
		std::cerr << "resources is empty" << std::endl;
		return 1;
	}
#define CHECK_NULL(var){if(!var){printf(#var" is null"); return 1;}}

	_root = new Ogre::Root(vm["plugins"].as<std::string>());
	CHECK_NULL(_root);

	Ogre::ConfigFile cf;
	cf.load(vm["resources"].as<std::string>());

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String sectionName, typeName, archName;

	while(seci.hasMoreElements()){
		sectionName = seci.peekNextKey();

		Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for( i = settings->begin(); i != settings->end(); ++i ){
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().
					addResourceLocation(archName, typeName, sectionName);
		}
	}

	if(_root->restoreConfig() || _root->showConfigDialog()){
		_renderWindow = _root->initialise(true, "OGRE OpenCV Visualizer");
	}else{
		return false;
	}

	_sceneManager = _root->createSceneManager(Ogre::ST_GENERIC);

	_camera = _sceneManager->createCamera("MainCamera");
	_camera->setPosition(20, 20, 20);
	_camera->setPosition(0, 0, 80);
	_camera->lookAt(0,0,0);
	_camera->setNearClipDistance(0.1f);
	_camera->setFarClipDistance(1000.f);

	Ogre::Viewport* vp = _renderWindow->addViewport(_camera);
	vp->setBackgroundColour(Ogre::ColourValue(.1f, .4f, .1f, 1.f));

	_camera->setAspectRatio( vp->getActualWidth() / float(vp->getActualHeight()) );

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	/*
	 * scene construction
	 */

	Ogre::TexturePtr screenTexture = Ogre::TextureManager::getSingleton().
			createManual(
					"ScreenTex",
					Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
					Ogre::TEX_TYPE_2D,
					camC,
					camR,
					0,
					Ogre::PF_R8G8B8,
					Ogre::TU_DYNAMIC);

	Ogre::MaterialPtr screenMaterial = Ogre::MaterialManager::getSingleton().
			create("ScreenMat", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	screenMaterial->getTechnique(0)->getPass(0)->createTextureUnitState("ScreenTex");

	Ogre::Rectangle2D* screenRect = new Ogre::Rectangle2D(true);
	screenRect->setCorners(-1.0, 1.0, 1.0, -1.0);
	screenRect->setMaterial("ScreenMat");
	screenRect->setRenderQueueGroup(Ogre::RENDER_QUEUE_BACKGROUND);

	Ogre::AxisAlignedBox aabInf;
	aabInf.setInfinite();
	screenRect->setBoundingBox(aabInf);

	Ogre::SceneNode* screenNode = _sceneManager->getRootSceneNode()->createChildSceneNode("Screen");
	screenNode->attachObject(screenRect);

	/*
	 * end scene construction
	 */

	_sceneManager->setAmbientLight(Ogre::ColourValue(1.f, 1.f, 1.f));
	Ogre::Light* l = _sceneManager->createLight();
	l->setPosition(50, 50, 50);

	/*
	 * set listeners
	 */
	OIS::ParamList pl;
	size_t windowHandler = 0;
	std::stringstream windowHandleString;

	_renderWindow->getCustomAttribute("WINDOW", &windowHandler);
	windowHandleString << windowHandler;

	pl.insert(std::make_pair(std::string("WINDOW"), windowHandleString.str()));

	pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
	pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
	pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
	pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("false")));

	_inputManager = OIS::InputManager::createInputSystem(pl);

	_keyboard = (OIS::Keyboard*)_inputManager->createInputObject(OIS::OISKeyboard, true);
	_keyboardListener = new OOV_KeyListener();
	_keyboard->setEventCallback(_keyboardListener);

	_windowEventListener = new OOV_WindowListener();
	Ogre::WindowEventUtilities::addWindowEventListener(_renderWindow, _windowEventListener);

	_frameListener = new OOV_FrameListener(_keyboard, &vc, screenTexture, _windowEventListener);
	_root->addFrameListener(_frameListener);
	/*
	 * end set listeners
	 */

	_root->startRendering();

	return 0;
}


