/*
 * OpenGLES20GraphicService.cpp
 *
 *  Created on: 13.03.2013
 *      Author: pavel
 */

#include "OpenGLES20GraphicService.h"

#include <RGBTexture.h>
#include <GLTriangle.h>

#include <GLMatrix4x4.h>

#include <Mesh.h>

const char vertexSource[] =
		"uniform   mat4 uortho;"
		"attribute vec2 vpos;"
		"attribute vec2 atex;"
		"varying   vec2 vtex;"
		"void main(){"
		"    gl_Position = uortho * vec4(vpos, 0.0, 1.0);"
		"    vtex = atex;"
		"}"
		;
const char fragmentSource[] =
		"precision mediump float;"
		"varying vec2      vtex;"
		"uniform sampler2D stex;"
		"void main(){"
		"    gl_FragColor = texture2D(stex, vtex);"
		"}"
		;

const GLfloat side = 50.f;
const GLfloat vertexScr[] = {
		-side, -side,
		 side, -side,
		 side,  side,
		-side,  side
};
GLfloat texScr[] = {
		0.f, 0.f,
		1.f, 0.f,
		1.f, 1.f,
		0.f, 1.f,
};

const GLfloat colorScr[] = {
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
};

const GLushort indices[] = {
		1, 0, 2,
		3, 2, 0
};

const int32_t texSize = 1024;

const GLfloat dim = side;

//const GLfloat
//		right_ = dim, left_ = -dim,
//		top = -dim, bottom = dim,
//		near = dim, far = -dim;
//
//const GLfloat
//		r_l = right_ - left_,
//		t_b = top - bottom,
//		f_n = far - near,
//
//		tx = -(right_ + left_) / (right_ - left_),
//		ty = -(top + bottom) / (top - bottom),
//		tz = -(far + near)   / (far - near);

//const GLfloat uOrhto[] = {
//		2.f / r_l,    0.f,       0.f,       0.f,
//		0.f,          2.f / t_b, 0.f,       0.f,
//		0.f,          0.f,       2.f / f_n, 0.f,
//		0.f,          0.f,       0.f,       1.f
//};

const MeshVertex trim[] = {
		{  0,   0, 0,  0, 0, 1,  0, 0},
		{100,   0, 0,  0, 0, 1,  0, 0},
		{100, 100, 0,  0, 0, 1,  0, 0},
};
const GLuint trimver[] = {
		0, 1, 2
};

OpenGLES20GraphicService::OpenGLES20GraphicService(): _isInit(false) {
}

OpenGLES20GraphicService::~OpenGLES20GraphicService() {
}

GLfloat mod[16];
GLfloat mod1[16];

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

	const double dim = 200.0;
	const double aspect = _height / double(_width);
	glViewport(0, 0, _width, _height);
	LOGI_OGLES20GS("h = %d, w = %d", _height, _width);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	_program = createProgram(vertexSource, fragmentSource);
	if(!_program){
		LOGE_OGLES20GS("Creating program is failed!!!");
	}else{
		LOGI_OGLES20GS("vpos handle getting");
		_vpos = glGetAttribLocation(_program, "vpos");  Tools::glCheck("glGetAttribLocation");
		_atex = glGetAttribLocation(_program, "atex");  Tools::glCheck("glGetAttribLocation");
		_stex = glGetUniformLocation(_program, "stex"); Tools::glCheck("glGetUniformLocation");
		_uortho = glGetUniformLocation(_program, "uortho"); Tools::glCheck("glGetUniformLocation");
	}

	Mat im(texSize, texSize, CV_8UC3, Scalar(0, 100, 70));
	circle(im, Point(100, 100), 60, Scalar(170, 0,0), 7);

	_tex1 = new RGBTexture(im);
	_tr1  = new GLTriangle(_tex1, (GLfloat*)vertexScr, texScr, (GLfloat*)colorScr, (GLushort*)indices, 6);
//	_tr1  = new Mesh(trim, 3, trimver, 3);

	GLMatrix4x4::matrixIdentity(mod);
	GLMatrix4x4::matrixIdentity(mod1);

	_isInit = true;
	return STATUS_OK;
}
bool OpenGLES20GraphicService::isInit(){
	return _isInit;
}

void OpenGLES20GraphicService::deinit(){
	delete _tex1;
	delete _tr1;

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
	glClearColor(0.f, 0.6f, 0.1f, 1.f); Tools::glCheck("glClearColor");
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); Tools::glCheck("glClear");

//	glUseProgram(_program); Tools::glCheck("glUseProgram");
//
//	glActiveTexture(GL_TEXTURE0);
//	_tex1->bind();
//	glUniform1i(_stex, 0);

//	glEnableVertexAttribArray(_vpos); Tools::glCheck("glEnableVertexAttribArray 1");
//	glEnableVertexAttribArray(_atex); Tools::glCheck("glEnableVertexAttribArray 2");

//	glVertexAttribPointer(_vpos, 2, GL_FLOAT, GL_FALSE, 0, vertexScr); Tools::glCheck("glVertexAttribPointer");
//	glVertexAttribPointer(_atex, 2, GL_FLOAT, GL_FALSE, 0, texScr); Tools::glCheck("glVertexAttribPointer");

	GLfloat mr[16];
	GLMatrix4x4::matrixPosition(mod, 0, 0, -400);

	static GLfloat angle = 0.f;
	angle += 0.03f;
	GLfloat tr[16]; GLMatrix4x4::matrixIdentity(tr); GLMatrix4x4::matrixRotationZ(tr, angle);
	GLfloat tr1[16]; GLMatrix4x4::matrixIdentity(tr1);
	GLMatrix4x4::matrixMultyply(tr, mod1, tr1);

	GLMatrix4x4::matrixMultyply(mod, tr1, mr);

	GLfloat aR = _width / GLfloat(_height);

	GLfloat orhto[16];
	GLMatrix4x4::matrixProjection(orhto, 0.1, 10000, 54 * 3.1415 / 180, aR);

	GLfloat res[16];
	GLMatrix4x4::matrixMultyply(orhto, mr, res);

	glUniformMatrix4fv(_uortho, 1, false, res);

//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
	if(_tr1)
		_tr1->draw();

//	glDisableVertexAttribArray(_vpos);
//	glDisableVertexAttribArray(_atex);

	eglSwapBuffers(_display, _surface); Tools::glCheck("eglSwapBuffers");

}

void OpenGLES20GraphicService::setImage( Mat image ){
}

GLuint OpenGLES20GraphicService::loadShader( GLenum shaderType, const char* source ){
	GLuint shader = glCreateShader(shaderType);
	if(shader){
		glShaderSource(shader, 1, &source, 0);
		glCompileShader(shader);

		GLint compiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if(!compiled){
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
			if(infoLen){
				char* buf = new char[infoLen];
				if(buf){
					glGetShaderInfoLog(shader, infoLen, 0, buf);
					LOGE("loadShader", "Could not compile shader: %d,\n%s", shaderType, buf);
					delete buf;
				}
				glDeleteShader(shader);
				shader = 0;
			}
		}
	}
	return shader;
}

GLuint OpenGLES20GraphicService::createProgram( const char* vertexShader, const char* fragmentShader ){
	GLuint vs = loadShader(GL_VERTEX_SHADER, vertexShader);
	if(!vs){
		return 0;
	}
	GLuint fs = loadShader(GL_FRAGMENT_SHADER, fragmentShader);
	if(!fs){
		return 0;
	}

	GLuint program = glCreateProgram();
	if(program){
		glAttachShader(program, vs); GLERR;
		glAttachShader(program, fs); GLERR;

		glLinkProgram(program);
		GLint linkStatus = GL_FALSE;
		glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
		if(linkStatus != GL_TRUE){
			GLint bufLen = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLen);
			if(bufLen){
				char* buf = (char*)new char[bufLen];
				if(buf){
					glGetProgramInfoLog(program, bufLen, NULL, buf);
					LOGE_OGLES20GS("Could not link program");
					delete [] buf;
				}
			}
			glDeleteProgram(program);
			program = 0;
		}
	}
	return program;
}
