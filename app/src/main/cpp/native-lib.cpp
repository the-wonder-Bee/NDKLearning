#include <jni.h>
#include <string>
#include <android/log.h>
#include <threads.h>
#include "pthread.h"
#include "test.h"

//定义打印宏 __VA_ARGS__代表可变参数

jstring  stringFromJNI(JNIEnv* env, jobject /* this */) {
    std::string hello = "Hello from C++动态注册";
    return env->NewStringUTF(hello.c_str());
}





jint getSum(JNIEnv *env, jobject thiz, jint param1, jint param2) {
    return param1+param2;
}



jcharArray getChars(JNIEnv *env, jobject thiz, jchar p,
                                                       jchar q) {
    jcharArray  array = env->NewCharArray(2);
    jchar  *array1 = env->GetCharArrayElements(array, NULL);
    array1[0] = p;
    array1[1] = q;
    env->ReleaseCharArrayElements(array, array1, 0); //一定要释放，否则会乱码
    return array;
}

jbyteArray getByteArray(JNIEnv *env, jobject thiz, jbyte left,
                                                           jbyte right) {

    jbyteArray byteArray = env->NewByteArray((jsize)(right  - left));
    jbyte* byte_elements = env->GetByteArrayElements(byteArray, 0);
    for(jint i=0; i<env->GetArrayLength(byteArray); i++) {
        byte_elements[i] = i+10;
    }
    env->ReleaseByteArrayElements(byteArray, byte_elements, 0);
    return byteArray;
}

jbooleanArray getBooleanArray(JNIEnv *env, jobject thiz,
                                                              jboolean is_true, jint size) {
    jbooleanArray booleanArray = env->NewBooleanArray(size);
    jboolean *boolean_array_elements = env->GetBooleanArrayElements(booleanArray, 0);
    for (int i = 0; i < env->GetArrayLength(booleanArray); ++i) {
        boolean_array_elements[i] = is_true;
    }
    env->ReleaseBooleanArrayElements(booleanArray, boolean_array_elements, 0);
    return booleanArray;
}

jshortArray getShortArray(JNIEnv *env, jobject thiz, jshort left,
                                                            jshort right) {
    jshortArray shortArray = env->NewShortArray((jint)(right-left));
    jshort* short_array_elements = env->GetShortArrayElements(shortArray, 0);
    for (jint i = 0; i < env->GetArrayLength(shortArray); ++i) {
        short_array_elements[i] = i+20;
    }

    env->ReleaseShortArrayElements(shortArray, short_array_elements, 0);
    return shortArray;
}


jintArray getIntArray(JNIEnv *env, jobject thiz, jint left,
                                                            jint right) {
   jintArray intArray = env->NewIntArray(right-left);
   jint* int_array_elemets = env->GetIntArrayElements(intArray, 0);
    for (int i = 0; i < right-left; ++i) {
        int_array_elemets[i]  = i+30;
    }
   env->ReleaseIntArrayElements(intArray, int_array_elemets, 0);
    return intArray;
}

jfloatArray getFloatArray(JNIEnv *env, jobject obj,
                                                                    jint left, jint right, jfloat value){
    jfloatArray floatArray = env->NewFloatArray(right-left);
    jfloat* float_array_elements = env->GetFloatArrayElements(floatArray, 0);
    for (int i = 0; i < right - left; ++i) {
        float_array_elements[i] = value;
    }
    env->ReleaseFloatArrayElements(floatArray, float_array_elements, 0);
    return floatArray;
}

jdoubleArray getDoubleArray(JNIEnv *env, jobject obj,
                                                                    jint left, jint right, jdouble value){
    jdoubleArray double_array = env->NewDoubleArray(right-left);
    jdouble* double_array_elements = env->GetDoubleArrayElements(double_array, 0);
    for (int i = 0; i < right - left; ++i) {
        double_array_elements[i] = value;
    }
    env->ReleaseDoubleArrayElements(double_array, double_array_elements, 0);
    return double_array;
}


jobjectArray getStringArray(JNIEnv* env, jobject obj,

                                                                jint left, jint right, jstring value) {

    jstring str = env->NewStringUTF("java/lang/String");
//    const char *class_name = const_cast<const char*>(env->GetStringUTFChars(str, 0));

    jclass  class_instance = env->FindClass(const_cast<char *>("java/lang/String"));

    jobjectArray  stringArray = env->NewObjectArray(right-left, class_instance, value);
    env->DeleteLocalRef(class_instance);
    return stringArray;
}


jobject getStudent(JNIEnv* env, jobject obj)
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

void testVoid(JNIEnv *env, jobject thiz) {
    LOGD("testVoid","测试 void返回值");
}



jobject getStudentList(JNIEnv *env, jobject thiz, jint size) {

    char *list_name = "java/util/ArrayList";
    char *student_name = "com/wonderbee/myapplication/Student";
    jclass list_cls = env->FindClass(const_cast<char *>(list_name));
    jclass student_cls = env->FindClass(const_cast<char *>(student_name));

    jmethodID list_construct = env->GetMethodID(list_cls, "<init>", "()V");
    jmethodID student_construct = env->GetMethodID(student_cls, "<init>", "()V");
    jmethodID list_add = env->GetMethodID(list_cls, "add", "(ILjava/lang/Object;)V");
    jobject list = env->NewObject(list_cls, list_construct);
    for(int i=0; i<size; i++){
        jobject student = env->NewObject(student_cls, student_construct);
        env->CallVoidMethod(student, env->GetMethodID(student_cls, "setAge", "(I)V"), i);
        env->CallVoidMethod(list, list_add, i, student);
        env->DeleteLocalRef(student);
    }
    return list;
}


/**
 * 测试jni如何抛出异常
 * @param env
 * @param thiz
 */
void testThrowException(JNIEnv *env, jobject thiz){
    const char *exception_class_name = "java/lang/IllegalArgumentException";
    jclass exception_cls = env->FindClass(exception_class_name);
//    jmethodID construct_method = env->GetMethodID(exception_cls, "<init>", "(Ljava/lang/String;)V");
//    jobject obj = env->NewObject(exception_cls, construct_method, env->NewStringUTF("jni抛出非法异常"));
//    env->Throw(static_cast<jthrowable>(obj));
    if (exception_cls == NULL) {
        LOGE("testThrowException", "找不到异常");
    }
    env->ThrowNew(exception_cls, "jni抛出非法异常");  //抛出异常类
}


void testThread(JNIEnv *env, jobject thiz) {
    testThread1();
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
            {"stringFormJNI", "()Ljava/lang/String;", (void *)(stringFromJNI)},
            {"getSum", "(II)I", (void *)getSum},
            {"getByteArray", "(BB)[B", (void *)getByteArray},
            {"getShortArray", "(SS)[S", (void *)getShortArray},
            {"getChars", "(CC)[C", (void *)getChars},
            {"getIntArray", "(II)[I", (void*)getIntArray},
            {"getFloatArray", "(IIF)[F",(void *)getFloatArray},
            {"getDoubleArray", "(IID)[D", (void *)getDoubleArray},
            {"getBooleanArray", "(ZI)[Z", (void *)getBooleanArray},
            {"getStringArray", "(IILjava/lang/String;)[Ljava/lang/String;",(void *)getStringArray},
            {"getStudent", "()Lcom/wonderbee/myapplication/Student;", (void *)getStudent},
            {"testVoid", "()V", (void *)testVoid},
            {"testThrowException", "()V", (void *)testThrowException},
            {"getStudentList", "(I)Ljava/util/List;",(void*)getStudentList},
            {"testThread", "()V", (void *)testThread}
    };
    env->RegisterNatives(class_name, nativeMethod, sizeof(nativeMethod)/sizeof(nativeMethod[0]));
    return JNI_VERSION_1_6;
}
