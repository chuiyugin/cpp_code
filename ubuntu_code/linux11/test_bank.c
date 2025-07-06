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

typedef struct{
    int id;
    int balance;
    pthread_mutex_t mutex;
} Account;

// 具有以下状态：未初始化、初始化、上锁、没上锁、销毁..
Account acct1 = {1, 100, PTHREAD_MUTEX_INITIALIZER};

// 扣款函数
int withdraw(Account* acct, int money){
    pthread_mutex_lock(&acct->mutex);
    // 临界区，对共享资源操作
    if(acct->balance < money){
        return 0;
    }
    sleep(1);// 让某种调度出现的概率最大化
    acct->balance -= money;
    pthread_mutex_unlock(&acct->mutex);
    printf("%lu: withdraw %d\n",pthread_self(), money);
    return money;
}

// 子线程的执行流程
void* start_routine(void* args){
    withdraw(&acct1, 100);
    return NULL;
}

int main(int argc, char* argv[])
{
    // 主线程
    pthread_t tid1, tid2;
    int err = pthread_create(&tid1, NULL, start_routine, NULL);
    if(err){
        error(1, err, "pthread_create");
    }
    err = pthread_create(&tid2, NULL, start_routine, NULL);
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
    pthread_mutex_destroy(&acct1.mutex);
    // 打印账户余额
    printf("balance = %d\n", acct1.balance);

    // 注意事项：当主线程终止时，整个进程就终止了
    return 0;
}