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

class OOV_FrameListener: public Ogre::FrameListener{
public:
	OOV_FrameListener( OIS::Keyboard* keyboard ): _keyboard(keyboard){
	}
	virtual ~OOV_FrameListener(){}
	bool frameStarted(const Ogre::FrameEvent& event){
		_keyboard->capture();
		if(_keyboard->isKeyDown(OIS::KC_ESCAPE)){
			return false;
		}
		return true;
	}
	bool frameEnded(const Ogre::FrameEvent& event){
		return true;
	}
private:
	OIS::Keyboard* _keyboard;
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
				"./oov " <<
				std::endl;
		return 0;
	}

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
	_camera->setPosition(10, 10, -10);
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

	Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().createManual("Screen", "General");
	Ogre::SubMesh* subMesh = mesh->createSubMesh();

	mesh->sharedVertexData = new Ogre::VertexData;
	mesh->sharedVertexData->vertexCount = 6;

	Ogre::VertexDeclaration* decl = mesh->sharedVertexData->vertexDeclaration;
	size_t offset = 0;

	decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
	offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);

	decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_DIFFUSE);
	offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);

	Ogre::HardwareVertexBufferSharedPtr vertexBuffer = Ogre::HardwareBufferManager::
			getSingleton().createVertexBuffer(
					offset,
					mesh->sharedVertexData->vertexCount,
					Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);

	float* vertices = static_cast<float*>(vertexBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL));

	vertices[0] = 0; vertices[1] = 0; vertices[2] = 0;
	vertices[3] = 1; vertices[4] = 0; vertices[5] = 0;

	vertices[6] = 10; vertices[7] = 0; vertices[8] = 0;
	vertices[9] = 1; vertices[10] = 0; vertices[11] = 0;

	vertices[12] = 0; vertices[13] = 10; vertices[14] = 0;
	vertices[15] = 1; vertices[16] = 0; vertices[17] = 0;

	vertices[18] = 10; vertices[19] = 10; vertices[20] = 0;
	vertices[21] = 1; vertices[22] = 0; vertices[23] = 0;

	vertexBuffer->unlock();

	Ogre::HardwareIndexBufferSharedPtr* indexBuffer = Ogre::HardwareBufferManager::getSingleton().
			createIndexBuffer(Ogre::HardwareIndexBuffer::IT_16BIT, mesh->sharedVertexData->vertexCount, Ogre::HardwareBuffer::HBU_STATIC);

	uint16_t* indices = static_cast<uint16_t*>(indexBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL));

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	indices[3] = 3;
	indices[4] = 2;
	indices[5] = 1;

	indexBuffer->unlock();

	mesh->sharedVertexData->vertexBufferBinding->setBinding(0, vertexBuffer);
	subMesh->useSharedVertices = true;
	subMesh->indexData->indexBuffer = indexBuffer;
	subMesh->indexData->indexCount = mesh->sharedVertexData->vertexCount;
	subMesh->indexData->indexStart = 0;

	mesh->_setBounds(Ogre::AxisAlignedBox(0, 0, 0, 10, 10, 10));

	mesh->load();

	Ogre::Entity* screenEntity = _sceneManager->createEntity("ScreenEntity", "Screen", "General");
	Ogre::SceneNode* screenNode = _sceneManager->getRootSceneNode()->createChildSceneNode();
	screenNode->attachObject(screenEntity);
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

	_inputManager = OIS::InputManager::createInputSystem(pl);

	_keyboard = (OIS::Keyboard*)_inputManager->createInputObject(OIS::OISKeyboard, true);
	_keyboardListener = new OOV_KeyListener();
	_keyboard->setEventCallback(_keyboardListener);

	_frameListener = new OOV_FrameListener(_keyboard);
	_root->addFrameListener(_frameListener);
	/*
	 * end set listeners
	 */

	_root->startRendering();

	delete _root;

//	if(vc.isOpened()){
//		while(1){
//
//			cv::Mat im;
//			if( vc.grab() ){
//				if( vc.retrieve(im)){
//					cv::imshow("Image output window", im);
//				}
//			}
//			char c = cv::waitKey(1000/30);
//			if(c == 27){
//				break;
//			}
//		}
//	}else{
//		std::cerr << "can't open VideoCapture" << std::endl;
//	}
//	vc.release();

	return 0;
}


