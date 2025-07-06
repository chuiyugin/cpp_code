#include "BlockQ.h"

// 创建空的阻塞队列
BlockQ* blockq_create(void){
    BlockQ* q = (BlockQ*) calloc(1, sizeof(BlockQ));

    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->not_empty, NULL);
    pthread_cond_init(&q->not_full, NULL);

    return q;
}
