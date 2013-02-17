/*
 * tools.h
 *
 *  Created on: 03.02.2013
 *      Author: pavel
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#include <android/log.h>
#include <GLES/gl.h>

#define LOGD(tag, ...){(void)__android_log_print(ANDROID_LOG_DEBUG, tag, __VA_ARGS__);}
#define LOGE(tag, ...){(void)__android_log_print(ANDROID_LOG_ERROR, tag, __VA_ARGS__);}
#define LOGW(tag, ...){(void)__android_log_print(ANDROID_LOG_WARN, tag, __VA_ARGS__);}
#define LOGI(tag, ...){(void)__android_log_print(ANDROID_LOG_INFO, tag, __VA_ARGS__);}

#define GLERR {GLenum er = glGetError(); if(er) LOGE("glGetError", "glGetError = %d", er);}

#endif /* TOOLS_H_ */
