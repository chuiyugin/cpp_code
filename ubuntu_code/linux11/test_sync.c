#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>

// 具有以下状态：未初始化、初始化、上锁、没上锁、销毁..
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // 静态初始化，默认属性

// 子线程的执行流程
void* start_routine(void* args){
    long* value = (long*) args;
    for(int i=0; i<10000000; i++){
        pthread_mutex_lock(&mutex);
        (*value)++; // 临界区，对共享资源操作
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    // 主线程
    long* value = (long*)calloc(1, sizeof(long)); // *value = 0

    pthread_t tid1, tid2;
    int err = pthread_create(&tid1, NULL, start_routine, value);
    if(err){
        error(1, err, "pthread_create");
    }
    err = pthread_create(&tid2, NULL, start_routine, value);
    if(err){
        error(1, err, "pthread_create");
    }

    // 主线程：等待子线程结束
    err = pthread_join(tid1, NULL);
    if(err){
        error(1, err, "pthread_join %lu\n", tid1);
    }
    err = pthread_join(tid2, NULL);
    if(err){
        error(1, err, "pthread_join %lu\n", tid2);
    }

    // 销毁互斥锁
    pthread_mutex_destroy(&mutex);

    printf("value = %ld\n", *value);

    // 注意事项：当主线程终止时，整个进程就终止了
    return 0;
}