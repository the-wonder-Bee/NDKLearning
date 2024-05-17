//
// Created by liao on 2024/4/14.
//
#include <android/log.h>
#ifndef NDKLEARNING_TEST_H
#define NDKLEARNING_TEST_H
#include <stdio.h>
#define LOGD(TAG, ...) __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__)
#define LOGI(TAG, ...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
#define LOGE(TAG, ...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
void testThread1();
#endif //NDKLEARNING_TEST_H
