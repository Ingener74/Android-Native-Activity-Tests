/*
 * AndroidGraphicBuffer.h
 *
 *  Created on: 03.03.2013
 *      Author: pavel
 */

#ifndef ANDROIDGRAPHICBUFFER_H_
#define ANDROIDGRAPHICBUFFER_H_

#include <stdint.h>

#include "EGLDispatcher.h"

#include "tools.h"

#define LOGI_AGB(...){ LOGI("AndroidGraphicBuffer", __VA_ARGS__); }
#define LOGE_AGB(...){ LOGE("AndroidGraphicBuffer", __VA_ARGS__); }

class AndroidGraphicBuffer {
public:
	typedef EGLDispatcher::EGLRect AGBRect;
	enum {
	    /* buffer is never read in software */
	    GRALLOC_USAGE_SW_READ_NEVER   = 0x00000000,
	    /* buffer is rarely read in software */
	    GRALLOC_USAGE_SW_READ_RARELY  = 0x00000002,
	    /* buffer is often read in software */
	    GRALLOC_USAGE_SW_READ_OFTEN   = 0x00000003,
	    /* mask for the software read values */
	    GRALLOC_USAGE_SW_READ_MASK    = 0x0000000F,

	    /* buffer is never written in software */
	    GRALLOC_USAGE_SW_WRITE_NEVER  = 0x00000000,
	    /* buffer is never written in software */
	    GRALLOC_USAGE_SW_WRITE_RARELY = 0x00000020,
	    /* buffer is never written in software */
	    GRALLOC_USAGE_SW_WRITE_OFTEN  = 0x00000030,
	    /* mask for the software write values */
	    GRALLOC_USAGE_SW_WRITE_MASK   = 0x000000F0,

	    /* buffer will be used as an OpenGL ES texture */
	    GRALLOC_USAGE_HW_TEXTURE      = 0x00000100,
	    /* buffer will be used as an OpenGL ES render target */
	    GRALLOC_USAGE_HW_RENDER       = 0x00000200,
	    /* buffer will be used by the 2D hardware blitter */
	    GRALLOC_USAGE_HW_2D           = 0x00000C00,
	    /* buffer will be used with the framebuffer device */
	    GRALLOC_USAGE_HW_FB           = 0x00001000,
	    /* mask for the software usage bit-mask */
	    GRALLOC_USAGE_HW_MASK         = 0x00001F00,
	};

	enum{
//		HAL_PIXEL_FORMAT_RGBA_8888 = 1,
		HAL_PIXEL_FORMAT_RGBX_8888 = 2,
//		HAL_PIXEL_FORMAT_RGB_888   = 3,
		HAL_PIXEL_FORMAT_RGB_565   = 4,
//		HAL_PIXEL_FORMAT_BGRA_8888 = 5,
//		HAL_PIXEL_FORMAT_RGBA_5551 = 6,
//		HAL_PIXEL_FORMAT_RGBA_4444 = 7
	};

	AndroidGraphicBuffer( uint32_t width, uint32_t height, uint32_t usage, uint32_t format );
	virtual ~AndroidGraphicBuffer();

	int32_t lock( uint32_t usage, uint8_t** bits );
	int32_t unlock();

	void*   getNativeBuffer();

//	int32_t lock( uint32_t usage, const AGBRect& rect, uchar** bits );

private:
	bool _isError;

	uint8_t* _instance;
	uint32_t _usage;
};

#endif /* ANDROIDGRAPHICBUFFER_H_ */
