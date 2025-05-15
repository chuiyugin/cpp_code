#include <stdbool.h>

// 定义队列中的元素类型(申明一下TreeNode即可，在链接的时候会找到结构体的定义)
typedef struct tree_node TreeNode;
typedef TreeNode* E;

// 队列节点的结构
typedef struct node_s{
    E data;
    struct node_s*next;
} QueueNode;

// 队列的结构
typedef struct {
    QueueNode *front;  // 队列的头部
    QueueNode *rear;   // 队列的尾部
    int size;          // 队列长度
} LinkedListQueue;

// 函数声明
LinkedListQueue* create_queue();                       // 创建一个空队列
void destroy_queue(LinkedListQueue* queue);            // 销毁队列，释放所有资源
bool is_empty(LinkedListQueue* q);
bool enqueue(LinkedListQueue* queue, E element);  // 入队操作
E dequeue(LinkedListQueue* queue); // 出队操作

E peek_queue(LinkedListQueue* queue);   // 获取队首元素，但不出队