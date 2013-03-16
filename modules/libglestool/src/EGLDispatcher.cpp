/*
 * EGLDispatcher.cpp
 *
 *  Created on: 03.03.2013
 *      Author: pavel
 */

#include "EGLDispatcher.h"

static const char* ANDROID_LIBUI_PATH = "libui.so";

EGLDispatcher::EGLDispatcher() {
}

EGLDispatcher::~EGLDispatcher() {
}

bool EGLDispatcher::init() {
	eglCreateImageKHR = (PFNEGLCREATEIMAGEKHRPROC) eglGetProcAddress(
			"eglCreateImageKHR");
	LOGI_EGLD("pfneglCreateImageKHR = %d", eglCreateImageKHR);

	glEGLImageTargetTexture2DOES =
			(PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) eglGetProcAddress(
					"glEGLImageTargetTexture2DOES");
	LOGI_EGLD(
			"pfnglEGLImageTargetTexture2DOES = %d", glEGLImageTargetTexture2DOES);

	eglDestroyImageKHR = (PFNEGLDESTROYIMAGEKHRPROC) eglGetProcAddress(
			"eglDestroyImageKHR");
	LOGI_EGLD("pfneglDestroyImageKHR = %d", eglDestroyImageKHR);

	void* handle = dlopen(ANDROID_LIBUI_PATH, RTLD_LAZY);
	if (!handle) {
		return false;
	}

	GraphicBufferCtor = (pfnGraphicBufferCtor) dlsym(handle,
			"_ZN7android13GraphicBufferC1Ejjij");
	GraphicBufferDtor = (pfnGraphicBufferDtor) dlsym(handle,
			"_ZN7android13GraphicBufferD1Ev");

	GraphicBufferLock = (pfnGraphicBufferLock) dlsym(handle,
			"_ZN7android13GraphicBuffer4lockEjPPv");
	GraphicBufferLockRect = (pfnGraphicBufferLockRect) dlsym(handle,
			"_ZN7android13GraphicBuffer4lockEjRKNS_4RectEPPv");
	GraphicBufferUnlock = (pfnGraphicBufferUnlock) dlsym(handle,
			"_ZN7android13GraphicBuffer6unlockEv");

	GraphicBufferGetNativeBuffer = (pfnGraphicBufferGetNativeBuffer) dlsym(
			handle, "_ZNK7android13GraphicBuffer15getNativeBufferEv");
	GraphicBufferReallocate = (pfnGraphicBufferReallocate) dlsym(handle,
			"_ZN7android13GraphicBuffer10reallocateEjjij");

	if (eglCreateImageKHR && eglDestroyImageKHR && glEGLImageTargetTexture2DOES
			&& GraphicBufferCtor && GraphicBufferDtor && GraphicBufferLock
			&& GraphicBufferLockRect && GraphicBufferUnlock
			&& GraphicBufferGetNativeBuffer && GraphicBufferReallocate) {
		LOGI_EGLD("EGL Dispather init success");
		return true;
	} else {
		LOGI_EGLD("EGL Dispather init error");
		return false;
	}
}

bool EGLDispatcher::isInit() {
	if (eglCreateImageKHR && eglDestroyImageKHR && glEGLImageTargetTexture2DOES
			&& GraphicBufferCtor && GraphicBufferDtor && GraphicBufferLock
			&& GraphicBufferLockRect && GraphicBufferUnlock
			&& GraphicBufferGetNativeBuffer && GraphicBufferReallocate) {
		return true;
	} else {
		return false;
	}
}

PFNEGLCREATEIMAGEKHRPROC EGLDispatcher::eglCreateImageKHR = 0;
PFNGLEGLIMAGETARGETTEXTURE2DOESPROC EGLDispatcher::glEGLImageTargetTexture2DOES =
		0;
PFNEGLDESTROYIMAGEKHRPROC EGLDispatcher::eglDestroyImageKHR = 0;

EGLDispatcher::pfnGraphicBufferCtor EGLDispatcher::GraphicBufferCtor = 0;
EGLDispatcher::pfnGraphicBufferDtor EGLDispatcher::GraphicBufferDtor = 0;

EGLDispatcher::pfnGraphicBufferLock EGLDispatcher::GraphicBufferLock = 0;
EGLDispatcher::pfnGraphicBufferLockRect EGLDispatcher::GraphicBufferLockRect = 0;
EGLDispatcher::pfnGraphicBufferUnlock EGLDispatcher::GraphicBufferUnlock = 0;

EGLDispatcher::pfnGraphicBufferGetNativeBuffer EGLDispatcher::GraphicBufferGetNativeBuffer =
		0;
EGLDispatcher::pfnGraphicBufferReallocate EGLDispatcher::GraphicBufferReallocate =
		0;
