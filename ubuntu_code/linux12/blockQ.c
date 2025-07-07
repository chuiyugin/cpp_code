#include "blockQ.h"

// 创建空的阻塞队列
BlockQ* blockq_create(void){
    BlockQ* q = (BlockQ*) calloc(1, sizeof(BlockQ));

    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->not_empty, NULL);
    pthread_cond_init(&q->not_full, NULL);

    return q;
}

void blockq_destroy(BlockQ* q){
    pthread_mutex_destroy(&q->mutex);
    pthread_cond_destroy(&q->not_empty);
    pthread_cond_destroy(&q->not_full);

    free(q);
}

void blockq_push(BlockQ* q, E val){
    // 获取锁
    pthread_mutex_lock(&q->mutex);
    // 注意事项：一定要写成while，当线程返回时再次检查队列未满
    while(q->size == N){
        // 1. 释放q->mutex
        // 2. 该线程陷入阻塞状态
        // 3. 当pthread_cond_wait返回时，一定再一次获取了q->mutex
        pthread_cond_wait(&q->not_full, &q->mutex);
    } // a. 获取了q->mutex; b. q->size != N

    q->elements[q->rear] = val;
    q->rear = (q->rear + 1) % N;
    q->size++;
    // 此时not_empty的条件成立，唤醒not_empty条件的线程
    pthread_cond_signal(&q->not_empty);
    // 释放锁
    pthread_mutex_unlock(&q->mutex);
}

E blockq_pop(BlockQ* q){
    // 获取锁
    pthread_mutex_lock(&q->mutex);
    // 注意事项：一定要写成while，当线程返回时再次检查队列未满
    while(q->size == 0){
        // 1. 释放q->mutex
        // 2. 该线程陷入阻塞状态
        // 3. 当pthread_cond_wait返回时，一定再一次获取了q->mutex
        pthread_cond_wait(&q->not_empty, &q->mutex);
    } // a. 获取了q->mutex; b. q->size != 0

    E ret = q->elements[q->front];
    q->front = (q->front + 1) % N;
    q->size++;
    // 此时not_full的条件成立，唤醒not_full条件的线程
    pthread_cond_signal(&q->not_full);
    // 释放锁
    pthread_mutex_unlock(&q->mutex);

    return ret;
}

bool blockq_full(BlockQ* q){
    pthread_mutex_lock(&q->mutex);
    int size = q->size;
    pthread_mutex_unlock(&q->mutex);
    return size == N;
}

bool blockq_empty(BlockQ* q){
    pthread_mutex_lock(&q->mutex);
    int size = q->size;
    pthread_mutex_unlock(&q->mutex);
    return size == 0;
}