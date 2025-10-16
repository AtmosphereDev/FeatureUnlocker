#pragma once

#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "LeviLogger", __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, "LeviLogger", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "LeviLogger", __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "LeviLogger", __VA_ARGS__)