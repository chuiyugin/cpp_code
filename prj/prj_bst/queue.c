#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

// 函数声明
LinkedListQueue* create_queue() {
    LinkedListQueue* q = calloc(1, sizeof(LinkedListQueue));
    q->size = 0;
    return q;
}

void destroy_queue(LinkedListQueue* q) {
  // 从队头开始遍历链表，销毁每一个结点
  QueueNode* current = q->front;
  while (current != NULL) {
    QueueNode* temp = current->next;
    free(current);
    current = temp;
  }
  // 销毁队列结构体
  free(q);
}

bool is_empty(LinkedListQueue* q) {
  // 队头指针是空指针，即表示空队列
  return q->front == NULL;
}

// 入队操作: 只能在队尾插入一个结点
// 由于已存在尾指针，所以这里的操作就是链表尾插
bool enqueue(LinkedListQueue* q, E element) {
  QueueNode* new_node = malloc(sizeof(QueueNode));
  if (new_node == NULL) {
    printf("Error: malloc failed in enqueue.\n");
    return false;
  }
  // 初始化新结点
  new_node->data = element;
  new_node->next = NULL;

  // 开始进行尾插法插入一个结点
  // 分两种情况：如果尾插插入的是第一个结点需要同步更新头指针，否则仅需要更新尾指针
  if (q->front == NULL) {
    // 插入的是第一个结点
    q->front = new_node;
    q->rear = new_node;
  }
  else {
    // 插入的不是第一个结点
    q->rear->next = new_node;
    q->rear = new_node;
  }
  q->size++;
  return true;
}

// 出队，在队头删除一个结点。也就是在删除链表的第一个结点
E dequeue(LinkedListQueue* q) {
  if (is_empty(q)) {
    printf("Error: queue is empty.\n");
    exit(1);
  }

  QueueNode* tmp = q->front;
  // 将出队的结点数据保存
  E remove_data = tmp->data;

  // 更新队头指针
  q->front = tmp->next;
  if (q->front == NULL) {
    // 如果队头更新后,队列为空,说明出队的就是最后一个元素
    // 于是同步更新队尾指针
    q->rear = NULL;
  }

  free(tmp);
  q->size--;
  return remove_data;
}

// 访问队头元素但不出队
E peek_queue(LinkedListQueue* q) {
  if (is_empty(q)) {
    printf("Error: queue is empty.\n");
    exit(1);
  }
  return q->front->data;
}