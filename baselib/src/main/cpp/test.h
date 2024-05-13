//
// Created by liao on 2024/4/14.
//

#ifndef NDKLEARNING_TEST_H
#define NDKLEARNING_TEST_H
#include <jni.h>
#include <stdio.h>
#include <android/log.h>

//定义打印宏 __VA_ARGS__代表可变参数
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,"##Jni:DRM",__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,"##Jni:DRM",__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,"##Jni:DRM",__VA_ARGS__)
JNIEnv *ENV;
#endif //NDKLEARNING_TEST_H
