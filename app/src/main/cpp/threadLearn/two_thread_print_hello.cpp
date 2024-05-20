//
// Created by 廖 on 2024/5/20.
//

#include "two_thread_print_hello.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int num;
void* result_thread;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t pthreadCond_1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t pthreadCond_2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t pthreadCond_3 = PTHREAD_COND_INITIALIZER;

int sy = 1;

void* printHello(void *pVoid)
{
    while (num < 50) {
        pthread_mutex_lock(&mutex);
        if (sy != 1) {
            pthread_cond_wait(&pthreadCond_1, &mutex);
        }
        char name[16];
        pthread_getname_np(pthread_self(), name, 16);
        if (num < 50) {
            LOGD("NDK", "%s hello: %d",name, num++);
        }
        sy = 2;
        pthread_cond_signal(&pthreadCond_2);
        pthread_mutex_unlock(&mutex);
   }
    return 0;
}

void* printHello2(void *pVoid)
{
    while (num < 50) {
        pthread_mutex_lock(&mutex);
        if (sy != 2) {
            pthread_cond_wait(&pthreadCond_2, &mutex);
        }
        char name[16];
        pthread_getname_np(pthread_self(), name, 16);
        if (num < 50) {
            LOGD("NDK", "%s hello: %d",name, num++);
        }
        sy = 3;
        pthread_cond_signal(&pthreadCond_3);
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}

void* printHello3(void *pVoid)
{
    while (num < 50) {
        pthread_mutex_lock(&mutex);
        if (sy != 3) {
            pthread_cond_wait(&pthreadCond_3, &mutex);
        }
        char name[16];
        pthread_getname_np(pthread_self(), name, 16);
        if (num < 50) {
            LOGD("NDK", "%s hello: %d",name, num++);
        }
        sy = 1;
        pthread_cond_signal(&pthreadCond_1);
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}

void thread_first(){
    pthread_t pthread;
    int res = pthread_create(&pthread, NULL, printHello, NULL);
    pthread_setname_np(pthread, "first");
    if (res != 0) {
        _exit(0);
    }
}

void thread_Second(){
    pthread_t pthread;
    int res = pthread_create(&pthread, NULL, printHello2, NULL);
    pthread_setname_np(pthread, "second");
    if (res != 0) {
        _exit(0);
    }
}

void thread_third(){
    pthread_t pthread;
    int res = pthread_create(&pthread, NULL, printHello3, NULL);
    pthread_setname_np(pthread, "third");
    if (res != 0) {
        _exit(0);
    }
}


void printNum(){
    thread_first();
    thread_Second();
    thread_third();
}

