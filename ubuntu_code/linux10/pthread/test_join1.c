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

typedef struct {
    int* arr;
    int left;
    int right;
} Section;

// 子线程的执行流程
void* start_routine(void* args){
    Section* sec = (Section*) args;
    // 在子线程中访问主线程栈里面的数据
    int sum = 0;
    for(int i=sec->left; i<=sec->right; i++){
        sum += sec->arr[i];
    }
    // 子线程两种返回方式（返回即终止）
    pthread_exit((void*)sum);
    //return (void*)sum;
    return NULL;
}

int main(int argc, char* argv[])
{
    // 主线程
    int arr[100];
    for(int i=1; i<=100; i++){
        arr[i-1] = i;
    }

    pthread_t tid1, tid2;

    Section sec1 = {arr, 0, 49};
    int err = pthread_create(&tid1, NULL, start_routine, (void*)&sec1);
    if(err){
        error(1, err, "pthread_create");
    }

    Section sec2 = {arr, 50, 99};
    err = pthread_create(&tid2, NULL, start_routine, (void*)&sec2);
    if(err){
        error(1, err, "pthread_create");
    }

    // 主线程：等待子线程结束，并接收返回值
    int result1;
    err = pthread_join(tid1, (void**)&result1);
    if(err){
        error(1, err, "pthread_join %lu\n", tid1);
    }
    int result2;
    err = pthread_join(tid2, (void**)&result2);
    if(err){
        error(1, err, "pthread_join %lu\n", tid2);
    }

    printf("main: sum = %d\n", result1+result2);

    // 注意事项：当主线程终止时，整个进程就终止了
    return 0;
}