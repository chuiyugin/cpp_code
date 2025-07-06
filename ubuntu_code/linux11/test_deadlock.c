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
    char name[25];
    int balance;
    // 细粒度锁
    pthread_mutex_t mutex;
} Account;

// 具有以下状态：未初始化、初始化、上锁、没上锁、销毁..
pthread_mutex_t protection = PTHREAD_MUTEX_INITIALIZER; // 保护获取锁原子操作的全局锁
Account acct1 = {1, "doncic", 10000, PTHREAD_MUTEX_INITIALIZER};
Account acct2 = {2, "jokic", 100, PTHREAD_MUTEX_INITIALIZER};


// 转账函数，A转账给B
int transfer(Account* acctA, Account* acctB, int money){
    // // 破坏循环等待
    // if(acctA->id < acctB->id){
    //     pthread_mutex_lock(&acctA->mutex);
    //     sleep(1);// 让某种调度出现的概率最大化
    //     pthread_mutex_lock(&acctB->mutex);
    // }
    // else{
    //     pthread_mutex_lock(&acctB->mutex);
    //     sleep(1);// 让某种调度出现的概率最大化
    //     pthread_mutex_lock(&acctA->mutex);
    // }

//     // 不能抢占
// start:
//     pthread_mutex_lock(&acctA->mutex);
//     sleep(1);
//     int err = pthread_mutex_trylock(&acctB->mutex);
//     if(err){
//         // 主动释放获取的锁
//         pthread_mutex_unlock(&acctA->mutex);
//         int seconds = rand() % 2;
//         sleep(seconds);
//         goto start;
//     }

    //持有并等待
    pthread_mutex_lock(&protection);
    pthread_mutex_lock(&acctA->mutex);
    sleep(1);
    pthread_mutex_lock(&acctB->mutex);
    pthread_mutex_unlock(&protection);


    // 临界区，对共享资源操作
    if(acctA->balance < money){
        pthread_mutex_unlock(&acctA->mutex);
        pthread_mutex_unlock(&acctB->mutex);
        return 0;
    }
    
    acctA->balance -= money;
    acctB->balance += money;

    pthread_mutex_unlock(&acctA->mutex);
    pthread_mutex_unlock(&acctB->mutex);
    
    return money;
}

// 子线程的执行流程
void* start_routine1(void* args){
    int money = (int) args;
    int ret = transfer(&acct1, &acct2, money);
    printf("%s -> %s: %d\n", acct1.name, acct2.name, ret);
    return NULL;
}
void* start_routine2(void* args){
    int money = (int) args;
    int ret = transfer(&acct2, &acct1, money);
    printf("%s -> %s: %d\n", acct2.name, acct1.name, ret);
    return NULL;
}

int main(int argc, char* argv[])
{
    // 主线程
    pthread_t tid1, tid2;
    int err = pthread_create(&tid1, NULL, start_routine1, (void*)900);
    if(err){
        error(1, err, "pthread_create");
    }
    err = pthread_create(&tid2, NULL, start_routine2, (void*)100);
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
    pthread_mutex_destroy(&acct2.mutex);
    // 打印账户余额
    printf("balance = %d\n", acct1.balance);
    printf("balance = %d\n", acct2.balance);

    // 注意事项：当主线程终止时，整个进程就终止了
    return 0;
}