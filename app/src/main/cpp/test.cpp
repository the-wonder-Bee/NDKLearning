//
// Created by liao on 2024/4/14.
//
#include <stdio.h>
#include "test.h"
#include <pthread.h>
#include <unistd.h>
#include "log/android_log_util.h"
void* res_p ;

void *printHelloWord(void *pVoid){
    int i = 0;
   while (i++ < 10) {
       LOGD("NDK","hello world");
       sleep(1);
   }
    res_p = (void *)10;
    return res_p;
}

void testThread1() {
    LOGD("NDK","testThread1");
   pthread_t pthread;
   int res = pthread_create(&pthread, NULL, printHelloWord, NULL);
   if (res) {
       LOGD("NDK","exit");
       _exit(0);
   }
   LOGD("NDK","thread return %d", res_p);
   pthread_join(pthread, &res_p);
   LOGD("NDK","thread return %d", res_p);

}