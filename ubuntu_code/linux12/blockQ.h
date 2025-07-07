#ifndef __WD_BLOCKQ_H
#define __WD_BLOCKQ_H

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
#include <stdbool.h>

#define N 1024

typedef int E;

// 循环数组实现队列
typedef struct {
    E elements[N];
    int front;
    int rear;
    int size;

    pthread_mutex_t mutex;
    pthread_cond_t not_empty; // 非空
    pthread_cond_t not_full; // 不满
} BlockQ;

// API 
BlockQ* blockq_create(void);
void blockq_destroy(BlockQ* q);

void blockq_push(BlockQ* q, E val);
E blockq_pop(BlockQ* q);
E blockq_peek(BlockQ* q);
bool blockq_empty(BlockQ* q);
bool blockq_full(BlockQ* q);

#endif