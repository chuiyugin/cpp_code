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

void print_ids(const char* prefix){
    printf("%s: ", prefix);
    printf("pid = %d, ppid = %d ", getpid(), getppid());
    printf("tid = %lu\n", pthread_self());
}

// 子线程的执行流程
void* start_routine(void* args){
    print_ids("child_thread");
    return NULL;
}

int main(int argc, char* argv[])
{
    // 主线程
    print_ids("main_thread");

    pthread_t tid;
    int err = pthread_create(&tid, NULL, start_routine, NULL);
    if(err){
        error(1, err, "pthread_create");
    }

    printf("main: new_thread = %lu\n", tid);

    // 注意事项：当主线程终止时，整个进程就终止了
    sleep(2);
    return 0;
}