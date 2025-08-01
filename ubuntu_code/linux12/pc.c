#include "blockQ.h"

typedef struct {
    pthread_t* threads; // 线程数组
    int nums; // 线程数目
    BlockQ* q;
} ThreadPool;

void* start_routine(void* args){
    ThreadPool* pool = (ThreadPool*) args;
    pthread_t tid = pthread_self();
    
    // 从阻塞队列中获取任务
    for(;;){
        E task_id = blockq_pop(pool->q);
        if(task_id == -1){
            pthread_exit(NULL);
        }
        printf("%lx: execute task %d\n", tid, task_id);
        sleep(1); // 模拟执行任务
        printf("%lx: task %d done!\n", tid, task_id);
    }
    return NULL;
}

ThreadPool* threadpool_create(int n){
    ThreadPool* pool = (ThreadPool*) malloc(sizeof(ThreadPool));
    pool->threads = (pthread_t*) malloc(n * sizeof(ThreadPool));
    pool->q = blockq_create();
    // 创建线程
    for(int i=0; i<n; i++){
        pthread_create(pool->threads+i, NULL, start_routine, (void*)pool);
    }
    return pool;
}

void threadpool_destroy(ThreadPool* pool){
    blockq_destroy(pool->q);
    free(pool->threads);
    free(pool);
}

int main(int argc, char* argv[]){
    // 1.创建线程池，并初始化
    ThreadPool* pool = threadpool_create(8);

    // 2.主线程生产任务
    for(int i=0; i<100; i++){
        blockq_push(pool->q, i+1);
    }
    sleep(13);

    // 3. 退出线程池
    for(int i=0; i<pool->nums; i++){
        blockq_push(pool->q, -1); // -1表示退出任务
    }
    for(int i=0; i<pool->nums; i++){
        pthread_join(pool->threads[i], NULL); // -1表示退出任务
    }

    // 4.销毁线程池
    threadpool_destroy(pool);

    return 0;
}