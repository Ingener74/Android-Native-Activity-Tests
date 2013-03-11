/*
 * EGLDispatcher.h
 *
 *  Created on: 03.03.2013
 *      Author: pavel
 */

#ifndef EGLDISPATCHER_H_
#define EGLDISPATCHER_H_

#include <dlfcn.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "tools.h"

#define LOGI_EGLD(...){ LOGI("EGL Dispatcher", __VA_ARGS__); }

class EGLDispatcher {
public:
	EGLDispatcher();
	virtual ~EGLDispatcher();

	typedef struct {
		int32_t left;
		int32_t top;
		int32_t right;
		int32_t bottom;
	} EGLRect;

	/*
	 * pointer to function definition
	 */
	typedef void (*pfnGraphicBufferCtor)(void*, uint32_t w, uint32_t h,
			uint32_t format, uint32_t usage);
	typedef void (*pfnGraphicBufferDtor)(void*);

	typedef int (*pfnGraphicBufferLock)(void*, uint32_t usage, uint8_t** addr);
	typedef int (*pfnGraphicBufferLockRect)(void*, uint32_t usage,
			const EGLRect&, uint8_t** addr);
	typedef int (*pfnGraphicBufferUnlock)(void*);

	typedef void* (*pfnGraphicBufferGetNativeBuffer)(void*);
	typedef int (*pfnGraphicBufferReallocate)(void*, uint32_t w, uint32_t h,
			uint32_t format);

	/*
	 * static pointers
	 */
	static PFNEGLCREATEIMAGEKHRPROC eglCreateImageKHR;
	static PFNGLEGLIMAGETARGETTEXTURE2DOESPROC glEGLImageTargetTexture2DOES;
	static PFNEGLDESTROYIMAGEKHRPROC eglDestroyImageKHR;

	static pfnGraphicBufferCtor GraphicBufferCtor;
	static pfnGraphicBufferDtor GraphicBufferDtor;

	static pfnGraphicBufferLock GraphicBufferLock;
	static pfnGraphicBufferLockRect GraphicBufferLockRect;
	static pfnGraphicBufferUnlock GraphicBufferUnlock;

	static pfnGraphicBufferGetNativeBuffer GraphicBufferGetNativeBuffer;
	static pfnGraphicBufferReallocate GraphicBufferReallocate;

	static bool init();
	static bool isInit();
};

#endif /* EGLDISPATCHER_H_ */
