#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashmap.h"

#define DEFAULT_CAPACITY 4
#define LOAD_FACTOR 0.75
#define MAX_PREALLOCATE 256

// 创建空的哈希表
HashMap* create_hashmap(void)
{
    HashMap* map = malloc(sizeof(HashMap));
    if(map == NULL)
    {
        printf("ERROR:malloc failed in create_hashmap!");
        exit(1);
    }

    map->size = 0;
    map->capacity = DEFAULT_CAPACITY;
    map->hash_seed = time(NULL);
    map->table = calloc(DEFAULT_CAPACITY,sizeof(KeyValueNode*));
    if(map->table == NULL)
    {
        printf("ERROR:calloc failed in create_hashmap!");
        exit(1);
    }

    return map;
}

// MurmurHash2函数
uint32_t hash(const void* key, int len, uint32_t seed) {
    const uint32_t m = 0x5bd1e995;  // 修正十六进制拼写错误
    const int r = 24;
    uint32_t h = seed ^ len;        // 正确初始化方式

    const unsigned char* data = (const unsigned char*)key;

    while (len >= 4) {
        uint32_t k = *(uint32_t*)data;

        k *= m;
        k ^= k >> r;  // 正确运算顺序
        k *= m;

        h *= m;
        h ^= k;        // 异或操作替代原错误乘法

        data += 4;
        len -= 4;
    }

    // 处理剩余字节
    switch (len) {
        case 3: h ^= data[2] << 16;
                // fall through
        case 2: h ^= data[1] << 8;
                // fall through
        case 1: h ^= data[0];
                h *= m;
    }

    // 最终混合
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}

//扩容函数的子函数
void rehash(KeyValueNode* cur,KeyValueNode** new_table,int new_capacity,uint32_t seed)
{
    //计算key的哈希值
    int len = strlen(cur->key);
    int idx = hash(cur->key,len,seed) % new_capacity;
    //头插法
    cur->next = new_table[idx];
    new_table[idx] = cur;
}

//对哈希表进行扩容
void grow_capacity(HashMap* map)
{
    //新的容量
    int new_capacity = (map->capacity <= MAX_PREALLOCATE)?
                    (map->capacity << 1) : (map->capacity + MAX_PREALLOCATE);
    //创建新的哈希数组
    KeyValueNode** new_table = calloc(new_capacity,sizeof(KeyValueNode*));
    if(new_table == NULL)
    {
        printf("ERROR:calloc failed in grow_capacity!");
        exit(1);
    }
    //重新设置哈希种子(更加安全)
    uint32_t new_seed = time(NULL);
    //将旧的哈希表迁移到新的哈希表上
    for(int i=0; i<map->capacity; i++)
    {
        KeyValueNode* cur = map->table[i];
        while(cur != NULL)
        {
            KeyValueNode* next = cur->next;
            //将旧表重映射到新表上
            rehash(cur,new_table,new_capacity,new_seed);
            cur = next;
        }
    }
    //释放旧的表
    free(map->table);

    //更新参数
    map->table = new_table;
    map->capacity = new_capacity;
    map->hash_seed = new_seed;
}


// 往哈希表添加元素
// a.如果key不存在，添加 key-val，并返回NULL
// b.如果key存在，更新key关联的val，返回原来的val
V put(HashMap* map, K key, V val)
{
    int idx = hash(key,strlen(key),map->table) % map->capacity;
    //遍历链表
    KeyValueNode* cur = map->table[idx];
    while(cur != NULL)
    {
        if(strcmp(cur->key,key) == 0)
        {
            //更新key关联的值，并返回原来的值
            V old_val = cur->val;
            cur->val = val;
            return old_val;
        }
        cur = cur->next;
    }
    //cur == NULL
    //a.如果key不存在，添加 key-val，并返回NULL
    KeyValueNode* new_node = malloc(sizeof(KeyValueNode));
    if(new_node == NULL)
    {
        printf("ERROR:malloc failed in put!");
        exit(1);
    }
    new_node->key = key;
    new_node->val = val;

    //判断是否需要扩容
    double table_load = (1.0 * map->size) / map->capacity;
    //如果超过负载因子就需要扩容
    if(table_load >= LOAD_FACTOR)
    {
        grow_capacity(map);
        //计算新的索引
        idx = hash(key,strlen(key),map->hash_seed) % map->capacity;
    }
    //头插法
    new_node->next = map->table[idx];//map->table[idx]哈希桶也存放着结点
    //链接
    map->table[idx] = new_node;
    //更新哈希表信息
    map->size++;

    return NULL;
}

// 根据key值，获取关联的值
// 如果key不存在，返回NULL
V get(HashMap* map, K key)
{
    //对key进行哈希，判断key在哪个哈希桶中
    int idx = hash(key,strlen(key),map->table) % map->capacity;
    //遍历链表
    KeyValueNode* cur = map->table[idx];
    while(cur != NULL)
    {
        if(strcmp(cur->key,key) == 0)
        {
            //找到了
            return cur->val;
        }
        cur = cur->next;
    }
    return NULL;
};

//删除键值对，如果key不存在，什么也不做
bool map_remove(HashMap* map, K key)
{
    int idx = hash(key,strlen(key),map->table) % map->capacity;
    //遍历链表
    KeyValueNode* pre = NULL;
    KeyValueNode* cur = map->table[idx];
    while(cur != NULL)
    {
        if(strcmp(cur->key,key) == 0)
        {
            //删除结点
            if(pre == NULL)
            {
                map->table[idx] = cur->next;
            }
            else
            {
                pre->next = cur->next;
            }
            free(cur);
            map->size--;
            return true;
        }
        pre = cur;
        cur = cur->next;
    }//cur == NULL,什么也不做
    return true;
}

// 销毁一个哈希表
void destroy_hashmap(HashMap* map)
{
    //释放所有结点(遍历哈希表)
    for(int i=0;i<map->capacity;i++)
    {
        KeyValueNode* cur = map->table[i];
        while(cur != NULL)
        {
            KeyValueNode* next = cur->next;
            free(cur);
            cur = next;
        }
    }
    //释放动态数组
    free(map->table);
    //释放HashMap结构体
    free(map);
}