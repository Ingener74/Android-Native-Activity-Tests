/*
 * tools.h
 *
 *  Created on: 03.02.2013
 *      Author: pavel
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#include <android/log.h>

#define LOGI(tag, ...)(__android_log_print(ANDROID_LOG_INFO,  tag, __VA_ARGS__))
#define LOGE(tag, ...)(__android_log_print(ANDROID_LOG_ERROR, tag, __VA_ARGS__))
#define LOGD(tag, ...)(__android_log_print(ANDROID_LOG_DEBUG, tag, __VA_ARGS__))
#define LOGW(tag, ...)(__android_log_print(ANDROID_LOG_WARN,  tag, __VA_ARGS__))

#endif /* TOOLS_H_ */
