#include <EGL/eglext.h>
#include <GLES2/gl2ext.h>
    
#ifdef	ANDROID
	GraphicBuffer * pGraphicBuffer = new GraphicBuffer(ImageWidth, ImageHeight, PIXEL_FORMAT_RGB_565, GraphicBuffer::USAGE_SW_WRITE_OFTEN | GraphicBuffer::USAGE_HW_TEXTURE);

	// Lock the buffer to get a pointer
	unsigned char * pBitmap = NULL;
	pGraphicBuffer->lock(GraphicBuffer::USAGE_SW_WRITE_OFTEN,(void **)&pBitmap);

	// Write 2D image to pBitmap

	// Unlock to allow OpenGL ES to use it
	pGraphicBuffer->unlock();

	EGLClientBuffer ClientBufferAddress = pGraphicBuffer->getNativeBuffer();
	EGLint SurfaceType = EGL_NATIVE_BUFFER_ANDROID;
#else
	EGLint SurfaceType = EGL_GL_TEXTURE_2D_KHR;
#endif

	// Make an EGL Image at the same address of the native client buffer
	EGLDisplay eglDisplayHandle = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	// Create an EGL Image with these attributes
	EGLint eglImageAttributes[] = {
		EGL_WIDTH, ImageWidth, 
		EGL_HEIGHT, ImageHeight, 
		EGL_MATCH_FORMAT_KHR,  
		EGL_FORMAT_RGB_565_KHR, 
		EGL_IMAGE_PRESERVED_KHR, 
		EGL_TRUE, 
		EGL_NONE
	};

	EGLImageKHR eglImageHandle = eglCreateImageKHR(eglDisplayHandle, EGL_NO_CONTEXT, SurfaceType, ClientBufferAddress, eglImageAttributes);

	// Create a texture and bind it to GL_TEXTURE_2D
	EGLint TextureHandle;
	glGenTextures(1, &TextureHandle);
	glBindTexture(GL_TEXTURE_2D, TextureHandle);

	// Attach the EGL Image to the same texture
	glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, eglImageHandle);
    
	// Get the address and pitch (stride) of the new texture image
	eglQuerySurface(eglDisplayHandle, eglImageHandle, EGL_BITMAP_POINTER_KHR, &BitmapAddress);
	eglQuerySurface(eglDisplayHandle, eglImageHandle, EGL_BITMAP_PITCH_KHR, &BitmapPitch);
	eglQuerySurface(eglDisplayHandle, eglImageHandle, EGL_BITMAP_ORIGIN_KHR, &BitmapOrigin);
    
	// Check for errors after each call to the EGL
	if (eglGetError() != EGL_SUCCESS)
		break;
    
	// Delete the EGL Image to free the memory when done	
	eglDestroyImageKHR(eglDisplayHandle, eglImageHandle);
