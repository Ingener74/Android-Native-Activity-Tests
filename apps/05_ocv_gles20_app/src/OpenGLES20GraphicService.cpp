/*
 * OpenGLES20GraphicService.cpp
 *
 *  Created on: 13.03.2013
 *      Author: pavel
 */

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OpenGLES20GraphicService.h"

#include <RGBTexture.h>
#include <Mesh.h>
#include <GLTriangle.h>
#include <OBJLoader.h>
#include <ShaderProgram.h>
#include <FileShaderLoader.h>
#include <RAWMeshExporter.h>

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

GLfloat  screenUVs[] = {
		0.f, 0.f,
		1.f, 0.f,
		1.f, 1.f,

		0.f, 0.f,
		1.f, 1.f,
		0.f, 1.f,
};

GLuint _MVP;
GLuint _aVert;
GLuint _aUVs;

FileShaderLoader* fsl;

/*
 * Object data
 */

/*
 * Data for both
 */

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

	projection = glm::perspective(56.f, _width / float(_height), 0.1f, 10000.f);

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

	_MVP   = screenProg->getUniform("MVP");
	_aVert = screenProg->getAttribute("aVert");
	_aUVs  = screenProg->getAttribute("aUVs");

	Mat screenIm(1024, 1024, CV_8UC3, Scalar(0, 100, 200));
	screenTex = new RGBTexture(screenIm, screenProg->getUniform("uTex"));
	if(!screenTex){
		LOGE_OGLES20GS("RGB texture is null");
		return STATUS_ERROR;
	}

	rawMeshExporter = new RAWMeshExporter(screenVert, screenUVs, NULL);

	screenMesh = new Mesh(rawMeshExporter, _aVert, screenTex, _aUVs);
	if(!screenMesh){
		LOGE_OGLES20GS("screen mesh is null");
		return STATUS_ERROR;
	}

/*
 *  Prepare object
 */

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

	LOGI_OGLES20GS("draw");

	glClearColor(0.5f, 0.9f, 0.5f, 1.f); Tools::glCheck("glClearColor");
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); Tools::glCheck("glClear");

	screenProg->useProgram();

	glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(0.f, 0.f, -200.f));
	glm::mat4 mvp   = projection * model;

	glUniformMatrix4fv(_MVP, 1, GL_FALSE, glm::value_ptr(mvp));

	screenMesh->draw();

	eglSwapBuffers(_display, _surface);

}

void OpenGLES20GraphicService::setImage( Mat image ){
	screenTex->updatePart(image);
}






