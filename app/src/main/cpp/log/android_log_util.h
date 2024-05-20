//
// Created by 廖 on 2024/5/20.
//

#ifndef NDKLEARNING_ANDROID_LOG_UTIL_H
#define NDKLEARNING_ANDROID_LOG_UTIL_H

#include <android/log.h>
#define LOGD(TAG, ...) __android_log_print(ANDROID_LOG_DEBUG,TAG, __VA_ARGS__)
#define LOGI(TAG, ...) __android_log_print(ANDROID_LOG_INFO,TAG, __VA_ARGS__)
#define LOGE(TAG, ...) __android_log_print(ANDROID_LOG_ERROR,TAG, __VA_ARGS__)

#endif //NDKLEARNING_ANDROID_LOG_UTIL_H
