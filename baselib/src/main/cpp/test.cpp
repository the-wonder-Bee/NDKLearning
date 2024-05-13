//
// Created by liao on 2024/4/14.
//

#include <string>
#include "test.h"


extern "C"
JNIEXPORT jstring
JNICALL getString(JNIEnv *env, jobject obj, jstring value){
    std::string val = "Hello MianClient, i come form jni: ";
    const char *jni_value = env->GetStringUTFChars(value, NULL);
    std::string jni_c_value =  jni_value;
    val += jni_c_value;
    return env->NewStringUTF(val.c_str());
}

extern "C"
JNIEXPORT jstring
JNICALL put(JNIEnv *env, jobject obj, jstring key, jstring value){
    std::string val = "Hello MianClient, i come form jni: ";
    const char *jni_value = env->GetStringUTFChars(value, NULL);
    const char *jni_key = env->GetStringUTFChars(key, NULL);
    std::string jni_c_value =  jni_value;
    std::string jni_c_key =  jni_value;
    val += jni_c_value;
    val += jni_key;
    return env->NewStringUTF(val.c_str());
}



extern "C"
JNIEXPORT jint
JNICALL JNI_OnLoad(JavaVM* vm, void* reserved){
    if (vm->GetEnv((void **)&ENV, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_FALSE;
    }
    jclass main_class = ENV->FindClass("com/wonderbee/baselib/MainClient");
    if (main_class == nullptr) {
        return JNI_FALSE;
    }
   //映射函数
   JNINativeMethod nativeMethod[] = {
           {"getString", "(Ljava/lang/String;)Ljava/lang/String;", (void *)getString},
           {"put", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;", (void *)put}
    };

    ENV->RegisterNatives(main_class, nativeMethod, sizeof(nativeMethod)/sizeof(nativeMethod[0]));
    return JNI_VERSION_1_6;
}
