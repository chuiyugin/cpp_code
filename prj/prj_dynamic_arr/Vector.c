#include "Vector.h"//""：搜索路径：当前目录 -> 系统的头文件包含的目录下


#define DEFAULT_CAPACITY 8
#define PREALLOC_MAX 1024 //提前申请的最大值

//构造函数（创建空的动态数组）
Vector* vector_create(void)
{
    Vector* v = malloc(sizeof(Vector));
    if(v==NULL)
    {
        printf("Error: malloc failed in vector_create!");
        exit(1);
    }
    E* p = malloc(DEFAULT_CAPACITY * sizeof(E));
    if(p == NULL)
    {
        free(v);//要将之前创建的v释放掉
        printf("Error: malloc failed in vector_create!");
        exit(1);
    }
    //设置基本参数
    v->elements = p;
    v->capacity = DEFAULT_CAPACITY;
    v->size = 0;

    return v;
}

//析构函数（释放动态数组）
Vector* vector_destroy(Vector* v)
{
    //从内到外释放（按照申请的相反顺序释放）
    free(v->elements);
    free(v);
}

void grow_capacity(Vector* v)
{
    int new_capacity = v->capacity < PREALLOC_MAX ?
        v->capacity * 2 : v->capacity+PREALLOC_MAX;
    
    //下面代码有问题，realloc失败会返回NULL，原来的内存空间不会被释放，造成内存泄漏
    //v->elements = realloc(v->elements,new_capacity * sizeof(E));
    E* p = realloc(v->elements,new_capacity * sizeof(E));
    if(p == NULL)
    {
        printf("Error: realloc failed in grow_capacity!");
        exit(1);
    }

    v->elements = p;
    v->capacity = new_capacity;
}

void push_back(Vector* v,E val)
{
    //判断是否需要扩容
    if(v->size == v->capacity)
    {
        grow_capacity(v);
    }
    //添加元素val
    v->elements[v->size++] = val;
}