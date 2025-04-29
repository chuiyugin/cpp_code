//头文件：类型的定义和API声明
#include <stddef.h>
#include <stdlib.h>

typedef int E;

typedef struct
{
    E* elements;
    int capacity;
    int size;
}Vector;

//函数声明
//构造函数
Vector* vector_create(void);

//析构函数
Vector* vector_destroy(Vector* v);

void push_back(Vector* v,E val);
