/*
 * OpenGLES20GraphicService.cpp
 *
 *  Created on: 13.03.2013
 *      Author: pavel
 */

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OpenGLES20GraphicService.h"

#include <RGBTexture.h>
#include <Mesh.h>
#include <extOBJLoader.h>
#include <ShaderProgram.h>
#include <FileShaderLoader.h>
#include <RAWMeshExporter.h>

#include <aruco.h>

/*
 * Screen data
 */
ShaderProgram* screenProg = NULL;

RAWMeshExporter* rawMeshExporter = NULL;
IObject*         screenMesh      = NULL;
IImageTexture*   screenTex       = NULL;

GLfloat  screenVert[] = {
	   -50.f, -50.f,  0.f,
		50.f, -50.f,  0.f,
		50.f,  50.f,  0.f,

	   -50.f, -50.f,  0.f,
	    50.f,  50.f,  0.f,
	   -50.f,  50.f,  0.f
};

uint32_t texSize = 1024;
GLfloat  tw = 640 / GLfloat(texSize);
GLfloat  th = 480 / GLfloat(texSize);

/*
 * 0-----------------1---------
 *
 *
 *
 *
 * 3---------------- 2
 *
 *
 * ----------------------------
 *
 */

GLfloat  screenUVs[] = {
		0.f,  th,
		 tw,  th,
		 tw, 0.f,

		0.f,  th,
		tw,  0.f,
		0.f, 0.f,
};

GLuint _MVP;
GLuint _aVert;
GLuint _aUVs;

FileShaderLoader* fsl;

/*
 * Object data
 */
IImageTexture* obj001_texture = NULL;
extOBJLoader*  obj001_loader  = 0;
IObject*       obj001         = NULL;

/*
 * Dirty car # 2
 */
extOBJLoader*  dirtyCarL   = NULL;
IObject*       dirtyCarObj = NULL;
IImageTexture* dirtyCarTex = NULL;

/*
 * Excavator # 6
 */
extOBJLoader*   excL       = NULL;
IObject*        excObj     = NULL;
IImageTexture*  excTex     = NULL;

/*
 * Exage # 8
 */
extOBJLoader*   exageL       = NULL;
IObject*        exageObj     = NULL;
IImageTexture*  exageTex     = NULL;

/*
 * OfficeChair # 18
 */

extOBJLoader*   chairL   = NULL;
IObject*        chairObj = NULL;
IImageTexture*  chairTex = NULL;

/*
 * Office Chair # 20
 */
extOBJLoader*   chairL2 = NULL;
IObject*        chairObj2 = NULL;
IImageTexture*  chairTex2 = NULL;

/*
 * Moto
 */

extOBJLoader*   motoL = NULL;
IObject*        motoObj = NULL;
IImageTexture*  motoTex = NULL;


/*
 * Plane
 */
extOBJLoader*   planeL = NULL;
IObject*        planeObj = NULL;
IImageTexture*  planeTex = NULL;


/*
 * Data for both
 */

aruco::CameraParameters  cameraParameters;
aruco::MarkerDetector    markerDetector;
vector<aruco::Marker>    markersFound;

glm::mat4 projection;

OpenGLES20GraphicService::OpenGLES20GraphicService(): _isInit(false),
		_display(EGL_NO_DISPLAY),
		_context(EGL_NO_CONTEXT),
		_surface(EGL_NO_SURFACE),

		_width(0),
		_height(0)
{
}

OpenGLES20GraphicService::~OpenGLES20GraphicService() {
}

OpenGLES20GraphicService::STATUS OpenGLES20GraphicService::init(
		android_app* application ){

	_application = application;

	const EGLint attribs[] = {
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_RED_SIZE,   8,
			EGL_GREEN_SIZE, 8,
			EGL_BLUE_SIZE,  8,
			EGL_DEPTH_SIZE, 8,
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
			EGL_NONE, EGL_NONE };

	EGLint format, numConf;
	EGLConfig config;

	_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	eglInitialize(_display, 0, 0);

	eglChooseConfig(_display, attribs, &config, 1, &numConf);

	eglGetConfigAttrib(_display, config, EGL_NATIVE_VISUAL_ID, &format);

	ANativeWindow_setBuffersGeometry(application->window, 0, 0, format);

	_surface = eglCreateWindowSurface(_display, config, application->window, NULL);

	EGLint contextAttr[] = {
			EGL_CONTEXT_CLIENT_VERSION, 2,
			EGL_NONE
	};
	_context = eglCreateContext(_display, config, NULL, contextAttr);

	if (eglMakeCurrent(_display, _surface, _surface, _context) == EGL_FALSE){
		LOGE_OGLES20GS("Unable to eglMakeCurrent");
		return IGraphicsService::STATUS_ERROR;
	}
	eglQuerySurface(_display, _surface, EGL_WIDTH, &_width);
	eglQuerySurface(_display, _surface, EGL_HEIGHT, &_height);

	glViewport(0, 0, _width, _height);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

//	GLfloat  screenVert[] = {
//		   -50.f, -50.f,  0.f,
//			50.f, -50.f,  0.f,
//			50.f,  50.f,  0.f,
//
//		   -50.f, -50.f,  0.f,
//		    50.f,  50.f,  0.f,
//		   -50.f,  50.f,  0.f
//	};



/*
 *  Prepare screen
 */
	fsl = new FileShaderLoader(
			"/sdcard/repo/data/screen.vert",
			"/sdcard/repo/data/screen.frag");

	if(fsl->isError()){
		LOGE_OGLES20GS("file shader loader>>> %s", fsl->errorString());
		return STATUS_ERROR;
	}else{
		LOGI_OGLES20GS("file shader loader success");
	}

	screenProg = new ShaderProgram(fsl);
	if(!screenProg->isError()){
		LOGE_OGLES20GS("shader program>>> %s", screenProg->errorString());
	}else{
		LOGI_OGLES20GS("shader program success");
	}

	_MVP   = screenProg->getUniform("MVP");     LOGI("gs init", "mvp   = %d", _MVP);
	_aVert = screenProg->getAttribute("aVert"); LOGI("gs init", "avert = %d", _aVert);
	_aUVs  = screenProg->getAttribute("aUVs");  LOGI("gs init", "auvs  = %d", _aUVs);

	Mat screenIm(1024, 1024, CV_8UC3, Scalar(0, 100, 200));
	screenTex = new RGBTexture(screenIm, screenProg->getUniform("uTex"));
	if(!screenTex){
		LOGE_OGLES20GS("RGB texture is null");
		return STATUS_ERROR;
	}

	rawMeshExporter = new RAWMeshExporter(6, screenVert, screenUVs, NULL);

	screenMesh = new Mesh(rawMeshExporter, _aVert, screenTex, _aUVs);
	if(!screenMesh){
		LOGE_OGLES20GS("screen mesh is null");
		return STATUS_ERROR;
	}

/*
 *  Prepare object
 */
//	Mat bw = imread("/sdcard/repo/data/brickwall.png");
	Mat bw = imread("/sdcard/repo/data/mesh003_1.png");
	cvtColor(bw, bw, CV_RGB2BGR);
	obj001_texture = new RGBTexture(bw);
	if(!obj001_texture){
		return STATUS_ERROR;
	}
//	obj001_loader = new extOBJLoader("/sdcard/repo/data/mesh005.obj");
	obj001_loader = new extOBJLoader("/sdcard/repo/data/mesh006.obj");
	if(!obj001_loader && obj001_loader->isError()){
		return STATUS_ERROR;
	}
	obj001 = new Mesh(obj001_loader, _aVert, obj001_texture, _aUVs);
	if(!obj001){
		return STATUS_ERROR;
	}

	/*
	 * Load Dirty Car
	 */
	Mat dirtyCarIm;
	cvtColor(imread("/sdcard/repo/data/dirtycar/car_white.png"), dirtyCarIm, CV_RGB2BGR);
	dirtyCarTex = new RGBTexture(dirtyCarIm);
	if(!dirtyCarTex) return STATUS_ERROR;

	dirtyCarL = new extOBJLoader("/sdcard/repo/data/dirtycar/dirty_car.obj");
	if(!dirtyCarL && dirtyCarL->isError()) return STATUS_ERROR;
	dirtyCarObj = new Mesh(dirtyCarL, _aVert, dirtyCarTex, _aUVs);

//	/*
//	 * load exc
//	 */
	Mat excIm;
	cvtColor(imread("/sdcard/repo/data/exc/exc.png"), excIm, CV_RGB2BGR);
	excTex = new RGBTexture(excIm);
	if(!excTex) return STATUS_ERROR;

	excL = new extOBJLoader("/sdcard/repo/data/exc/exc.obj");
	if(!excL && excL->isError()) return STATUS_ERROR;
	excObj = new Mesh(excL, _aVert, excTex, _aUVs);

	/*
	 * load exage
	 */
	Mat exageIm;
	cvtColor(imread("/sdcard/repo/data/exage/exage.png"), exageIm, CV_RGB2BGR);
	exageTex = new RGBTexture(exageIm);
	if(!exageTex) return STATUS_ERROR;

	exageL = new extOBJLoader("/sdcard/repo/data/exage/exage.obj");
	if(!exageL && exageL->isError()) return STATUS_ERROR;
	exageObj = new Mesh(exageL, _aVert, exageTex, _aUVs);

	/*
	 * load chair
	 */
	Mat chairIm;
	cvtColor(imread("/sdcard/repo/data/off_chair/office_chair_d.png"), chairIm, CV_RGB2BGR);
	chairTex = new RGBTexture(chairIm);
	if(!chairTex) return STATUS_ERROR;

	chairL = new extOBJLoader("/sdcard/repo/data/off_chair/office_chair.obj");
	if(!chairL && chairL->isError()) return STATUS_ERROR;
	chairObj = new Mesh(chairL, _aVert, chairTex, _aUVs);

	/*
	 * load chair 2
	 */
	Mat chairIm2;
	cvtColor(imread("/sdcard/repo/data/off_chair2/chair_operations_d.png"), chairIm2, CV_RGB2BGR);
	chairTex2 = new RGBTexture(chairIm2);
	if(!chairTex2) return STATUS_ERROR;

	chairL2 = new extOBJLoader("/sdcard/repo/data/off_chair2/chair_operations.obj");
	if(!chairL2 && chairL2->isError()) return STATUS_ERROR;
	chairObj2 = new Mesh(chairL2, _aVert, chairTex2, _aUVs);

	/*
	 * Moto
	 */
	Mat motoIm;
	cvtColor(imread("/sdcard/repo/data/moto/motorcycle_d.png"), motoIm, CV_RGB2BGR);
	motoTex = new RGBTexture(motoIm);
	if(!motoTex) return STATUS_ERROR;

	motoL = new extOBJLoader("/sdcard/repo/data/moto/motorcycle.obj");
	if(!motoL && motoL->isError()) return STATUS_ERROR;
	motoObj  = new Mesh(motoL, _aVert, motoTex, _aUVs);

	/*
	 * Plane
	 */
	Mat planeIm;
	cvtColor(imread("/sdcard/repo/data/plane/plane.png"), planeIm, CV_RGB2BGR);
	planeTex = new RGBTexture(planeIm);
	if(!planeTex) return STATUS_ERROR;

	planeL = new extOBJLoader("/sdcard/repo/data/plane/plane.obj");
	if(!planeL && planeL->isError()) return STATUS_ERROR;
	planeObj  = new Mesh(planeL, _aVert, planeTex, _aUVs);

/*
 * Prepare AR camera parameters
 */
	cameraParameters.readFromXMLFile("/sdcard/repo/data/camera.yml");
	cameraParameters.resize(Size(640, 480));

	double proj_ar[16];
	cameraParameters.glGetProjectionMatrix(Size(640, 480), Size(_width, _height), proj_ar, 0.1, 10000, false);
	float proj_ar32[16];
	for( uint32_t i = 0; i < 16; ++i ){
		proj_ar32[i] = proj_ar[i];
	}

//	projection = glm::perspective(56.f, _width / float(_height), 0.1f, 10000.f);
	projection = glm::make_mat4(proj_ar32);

	GLfloat sw = 3000.f;
	GLfloat sh = sw * 3.f / 4.f;

	screenVert[0] = -sw;  screenVert[1] = -sh;
	screenVert[3] =  sw;  screenVert[4] = -sh;
	screenVert[6] =  sw;  screenVert[7] =  sh;

	screenVert[9]  = -sw;  screenVert[10] = -sh;
	screenVert[12] =  sw;  screenVert[13] =  sh;
	screenVert[15] = -sw;  screenVert[16] =  sh;

	LOGW("gs init", "camera parameters loaded");

	LOGW("gs init", "init done");

	_isInit = true;
	return STATUS_OK;
}
bool OpenGLES20GraphicService::isInit(){
	return _isInit;
}

void OpenGLES20GraphicService::deinit(){

	if(_display != EGL_NO_DISPLAY){
		eglMakeCurrent(_display, _surface, _surface, _context);
		if(_context != EGL_NO_CONTEXT){
			eglDestroyContext(_display, _context);
		}
		if(_surface != EGL_NO_SURFACE){
			eglDestroySurface(_display, _surface);
		}
		eglTerminate(_display);
	}
	_display = EGL_NO_DISPLAY;
	_context = EGL_NO_CONTEXT;
	_surface = EGL_NO_SURFACE;
}

void OpenGLES20GraphicService::draw(){

//	LOGI_OGLES20GS("draw");

	glClearColor(0.5f, 0.9f, 0.5f, 1.f); Tools::glCheck("glClearColor");
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); Tools::glCheck("glClear");

	screenProg->useProgram();

	glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(0.f, 0.f, -1000.f));
	model = glm::rotate(model, 180.f, glm::vec3(0.f, 0.f, 1.f));
	model = glm::rotate(model, 180.f, glm::vec3(0.f, 1.f, 0.f));
	model = glm::translate(model, glm::vec3(140.f, 110.f, 0.f));
	model = glm::scale(model, glm::vec3(7.f, 5.f, 1.f));
	glm::mat4 mvp   = projection * model;

	glUniformMatrix4fv(_MVP, 1, GL_FALSE, glm::value_ptr(mvp)); Tools::glCheck("glUniformMatrix4fv");

	screenMesh->draw();

	/*
	 * draw objects
	 */
#define call_x(x){ if(x)x->draw(); }

	for( uint32_t i = 0; i < markersFound.size(); ++i ){
		if(markersFound[i].id == 4){
			double mvm[16];
			markersFound[i].glGetModelViewMatrix(mvm);

			if(mvm){
				float mvm32[16];
				for( uint32_t i = 0; i < 16; ++i ){
					mvm32[i] = mvm[i];
				}

				glm::mat4 mv = glm::make_mat4(mvm32);

				glm::mat4 mvp2 = projection * mv;

				glUniformMatrix4fv(_MVP, 1, GL_FALSE, value_ptr(mvp2));

				if(obj001)
					obj001->draw();

			}else{
				LOGE_OGLES20GS("mvm is null");
			}

		}
		if(markersFound[i].id == 2){
			double mvm[16];
			markersFound[i].glGetModelViewMatrix(mvm);

			float mvm32[16]; for( uint32_t i = 0; i < 16; ++i )mvm32[i] = mvm[i];

			glm::mat4 mv = glm::make_mat4(mvm32);
			glm::mat4 mvp2 = projection * mv;

			glUniformMatrix4fv(_MVP, 1, GL_FALSE, value_ptr(mvp2));

//			dirtyCarObj->draw();
			call_x(dirtyCarObj);
		}

		if(markersFound[i].id == 6 ){
			double mvm[16];
			markersFound[i].glGetModelViewMatrix(mvm);

			float mvm32[16]; for( uint32_t i = 0; i < 16; ++i )mvm32[i] = mvm[i];

			glm::mat4 mv = glm::make_mat4(mvm32);
			glm::mat4 mvp2 = projection * mv;

			glUniformMatrix4fv(_MVP, 1, GL_FALSE, value_ptr(mvp2));

//			excObj->draw();
			call_x(excObj);
		}

		if(markersFound[i].id == 8 ){
			double mvm[16];
			markersFound[i].glGetModelViewMatrix(mvm);

			float mvm32[16]; for( uint32_t i = 0; i < 16; ++i )mvm32[i] = mvm[i];

			glm::mat4 mv = glm::make_mat4(mvm32);
			glm::mat4 mvp2 = projection * mv;

			glUniformMatrix4fv(_MVP, 1, GL_FALSE, value_ptr(mvp2));

//			exageObj->draw();
			call_x(exageObj);
		}

		if(markersFound[i].id == 10 ){
			double mvm[16];
			markersFound[i].glGetModelViewMatrix(mvm);

			float mvm32[16]; for( uint32_t i = 0; i < 16; ++i )mvm32[i] = mvm[i];

			glm::mat4 mv = glm::make_mat4(mvm32);
			glm::mat4 mvp2 = projection * mv;

			glUniformMatrix4fv(_MVP, 1, GL_FALSE, value_ptr(mvp2));

//			motoObj->draw();
			call_x(motoObj);
		}

		if(markersFound[i].id == 12 ){
			double mvm[16];
			markersFound[i].glGetModelViewMatrix(mvm);

			float mvm32[16]; for( uint32_t i = 0; i < 16; ++i )mvm32[i] = mvm[i];

			glm::mat4 mv = glm::make_mat4(mvm32);
			glm::mat4 mvp2 = projection * mv;

			glUniformMatrix4fv(_MVP, 1, GL_FALSE, value_ptr(mvp2));

//			planeObj->draw();
			call_x(planeObj);
		}

		if(markersFound[i].id == 18){
			double mvm[16];
			markersFound[i].glGetModelViewMatrix(mvm);

			float mvm32[16]; for( uint32_t i = 0; i < 16; ++i )mvm32[i] = mvm[i];

			glm::mat4 mv = glm::make_mat4(mvm32);
			glm::mat4 mvp2 = projection * mv;

			glUniformMatrix4fv(_MVP, 1, GL_FALSE, value_ptr(mvp2));

//			chairObj->draw();
			call_x(chairObj);
		}

		if(markersFound[i].id == 20){
			double mvm[16];
			markersFound[i].glGetModelViewMatrix(mvm);

			float mvm32[16]; for( uint32_t i = 0; i < 16; ++i )mvm32[i] = mvm[i];

			glm::mat4 mv = glm::make_mat4(mvm32);
			glm::mat4 mvp2 = projection * mv;

			glUniformMatrix4fv(_MVP, 1, GL_FALSE, value_ptr(mvp2));

//			chairObj2->draw();
			call_x(chairObj2);
		}
	}

	eglSwapBuffers(_display, _surface);
}

void OpenGLES20GraphicService::setImage( Mat image ){

	if(image.cols && image.rows)
		markerDetector.detect(image, markersFound, cameraParameters.CameraMatrix, Mat(), 1);

	char buf[128];
	sprintf(buf, "num of marker = %d", markersFound.size());
	putText(image, buf, Point(20, 40), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255,255));

	for( uint16_t i = 0; i < markersFound.size(); ++i ){
		sprintf(buf, "marker id = %d", markersFound[i].id);
		putText(image, buf, Point(20, 60 + 20 * i), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255,255));
	}

	for( uint32_t i = 0; i < markersFound.size(); ++i ){
		if(markersFound[i].id == 4){
			double mvm[16];
			markersFound[i].glGetModelViewMatrix(mvm);
		}
	}
	screenTex->updatePart(image);
}






