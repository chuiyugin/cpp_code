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

void cleanup(void* args){
    char* msg = (char*) args;
    printf("cleanup: %s\n", msg);
}

// 子线程的执行流程
void* start_routine(void* args){
    // 注册线程清理函数
    pthread_cleanup_push(cleanup, "first");
    pthread_cleanup_push(cleanup, "second");
    pthread_cleanup_push(cleanup, "third");

    pthread_cleanup_pop(1); // 执行线程清理函数，打印third，执行顺序与注册顺序相反
    pthread_cleanup_pop(0); // 

    sleep(2);
    printf("child thread is going to return!\n");

    pthread_exit(NULL);
    // 后面的代码肯定不会执行
    pthread_cleanup_pop(0);

    return NULL;
}

int main(int argc, char* argv[])
{
    // 主线程
    pthread_t tid;
    int err = pthread_create(&tid, NULL, start_routine, NULL);
    if(err){
        error(1, err, "pthread_create");
    }
    // 主线程等待子线程
    err = pthread_join(tid, NULL);
    if(err){
        error(1, err, "pthread_join");
    }
    // 注意事项：当主线程终止时，整个进程就终止了
    return 0;
}