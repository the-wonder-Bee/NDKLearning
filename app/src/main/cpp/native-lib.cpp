#include <jni.h>
#include <string>
#include <android/log.h>

//定义打印宏 __VA_ARGS__代表可变参数
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,"##Jni:DRM",__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,"##Jni:DRM",__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,"##Jni:DRM",__VA_ARGS__)

jstring  stringFromJNI(JNIEnv* env, jobject /* this */) {
    std::string hello = "Hello from C++动态注册";
    return env->NewStringUTF(hello.c_str());
}





extern "C"
JNIEXPORT jint JNICALL
Java_com_wonderbee_myapplication_MainActivity_getSum(JNIEnv *env, jobject thiz, jint param1, jint param2) {
    return param1+param2;
}



extern "C"
JNIEXPORT jcharArray JNICALL
Java_com_wonderbee_myapplication_MainActivity_getChars(JNIEnv *env, jobject thiz, jchar p,
                                                       jchar q) {
    jcharArray  array = env->NewCharArray(2);
    jchar  *array1 = env->GetCharArrayElements(array, NULL);
    array1[0] = p;
    array1[1] = q;
    env->ReleaseCharArrayElements(array, array1, 0); //一定要释放，否则会乱码
    return array;
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_wonderbee_myapplication_MainActivity_getByteArray(JNIEnv *env, jobject thiz, jbyte left,
                                                           jbyte right) {

    jbyteArray byteArray = env->NewByteArray((jsize)(right  - left));
    jbyte* byte_elements = env->GetByteArrayElements(byteArray, 0);
    for(jint i=0; i<env->GetArrayLength(byteArray); i++) {
        byte_elements[i] = i+10;
    }
    env->ReleaseByteArrayElements(byteArray, byte_elements, 0);
    return byteArray;
}

extern "C"
JNIEXPORT jbooleanArray JNICALL
Java_com_wonderbee_myapplication_MainActivity_getBooleanArray(JNIEnv *env, jobject thiz,
                                                              jboolean is_true, jint size) {
    jbooleanArray booleanArray = env->NewBooleanArray(size);
    jboolean *boolean_array_elements = env->GetBooleanArrayElements(booleanArray, 0);
    for (int i = 0; i < env->GetArrayLength(booleanArray); ++i) {
        boolean_array_elements[i] = is_true;
    }
    env->ReleaseBooleanArrayElements(booleanArray, boolean_array_elements, 0);
    return booleanArray;
}

extern "C"
JNIEXPORT jshortArray JNICALL
Java_com_wonderbee_myapplication_MainActivity_getShortArray(JNIEnv *env, jobject thiz, jshort left,
                                                            jshort right) {
    jshortArray shortArray = env->NewShortArray((jint)(right-left));
    jshort* short_array_elements = env->GetShortArrayElements(shortArray, 0);
    for (jint i = 0; i < env->GetArrayLength(shortArray); ++i) {
        short_array_elements[i] = i+20;
    }

    env->ReleaseShortArrayElements(shortArray, short_array_elements, 0);
    return shortArray;
}


extern "C"
JNIEXPORT jintArray JNICALL
Java_com_wonderbee_myapplication_MainActivity_getIntArray(JNIEnv *env, jobject thiz, jint left,
                                                            jint right) {
   jintArray intArray = env->NewIntArray(right-left);
   jint* int_array_elemets = env->GetIntArrayElements(intArray, 0);
    for (int i = 0; i < right-left; ++i) {
        int_array_elemets[i]  = i+30;
    }
   env->ReleaseIntArrayElements(intArray, int_array_elemets, 0);
    return intArray;
}

extern "C"
JNIEXPORT jfloatArray
JNICALL Java_com_wonderbee_myapplication_MainActivity_getFloatArray(JNIEnv *env, jobject obj,
                                                                    jint left, jint right, jfloat value){
    jfloatArray floatArray = env->NewFloatArray(right-left);
    jfloat* float_array_elements = env->GetFloatArrayElements(floatArray, 0);
    for (int i = 0; i < right - left; ++i) {
        float_array_elements[i] = value;
    }
    env->ReleaseFloatArrayElements(floatArray, float_array_elements, 0);
    return floatArray;
}

extern "C"
JNIEXPORT jdoubleArray
JNICALL Java_com_wonderbee_myapplication_MainActivity_getDoubleArray(JNIEnv *env, jobject obj,
                                                                    jint left, jint right, jdouble value){
    jdoubleArray double_array = env->NewDoubleArray(right-left);
    jdouble* double_array_elements = env->GetDoubleArrayElements(double_array, 0);
    for (int i = 0; i < right - left; ++i) {
        double_array_elements[i] = value;
    }
    env->ReleaseDoubleArrayElements(double_array, double_array_elements, 0);
    return double_array;
}


extern "C"
JNIEXPORT jobjectArray
JNICALL Java_com_wonderbee_myapplication_MainActivity_getStringArray(JNIEnv* env, jobject obj,

                                                                jint left, jint right, jstring value) {

    jstring str = env->NewStringUTF("java/lang/String");
//    const char *class_name = const_cast<const char*>(env->GetStringUTFChars(str, 0));

    jclass  class_instance = env->FindClass(const_cast<char *>("java/lang/String"));

    jobjectArray  stringArray = env->NewObjectArray(right-left, class_instance, value);
    env->DeleteLocalRef(class_instance);
    return stringArray;
}


extern "C"
JNIEXPORT jobject
JNICALL Java_com_wonderbee_myapplication_MainActivity_getStudent(JNIEnv* env, jobject obj)
{
    jclass student_class_instance = env->FindClass(const_cast<char*>("com/wonderbee/myapplication/Student"));
    jmethodID  jmethodId = env->GetMethodID(student_class_instance, "<init>", "()V");
    jobject student = env->NewObject(student_class_instance, jmethodId);
    jmethodID  setname = env->GetMethodID(student_class_instance, "setName", "(Ljava/lang/String;)V");
    jmethodID  setage = env->GetMethodID(student_class_instance, "setAge", "(I)V");
    env->CallVoidMethod(student, setname,env->NewStringUTF("jerry"));
    env->CallVoidMethod(student, setage, 18);
    return student;
}


/**
 * 动态注册
 */
extern "C" JNIEXPORT jint
JNICALL JNI_OnLoad(JavaVM *vm, void *reversed) {
    JNIEnv *env = NULL;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_FALSE;
    }
    jclass class_name = env->FindClass("com/wonderbee/myapplication/MainActivity"); //找到需要加载的类
    if (class_name == nullptr) {
        return JNI_FALSE;
    }
    //native方法 第一个参数是 java中native方法名称  第二个参数是括号内是方法参数签名, 括号外是方法返回值签名  第三个参数是函数指针
    JNINativeMethod nativeMethod[] = {
            {"stringFormJNI", "()Ljava/lang/String;", (void *)(stringFromJNI)}
    };
    env->RegisterNatives(class_name, nativeMethod, 1);
    return JNI_VERSION_1_6;
}



extern "C"
JNIEXPORT void JNICALL
Java_com_wonderbee_myapplication_MainActivity_testVoid(JNIEnv *env, jobject thiz) {
    LOGD("测试 void返回值");
}