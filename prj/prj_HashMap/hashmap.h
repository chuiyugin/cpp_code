#include <stdint.h>
#include <stdbool.h>
#define CAPACITY 10

typedef char* K;
typedef char* V;

// 键值对结点
typedef struct node_s {
  K key;
  V val;
  struct node_s* next;
} KeyValueNode;

typedef struct {
  // 哈希桶
  KeyValueNode** table; // 二级指针
  // 存储的数量
  int size;
  // 容量大小
  int capacity;
  // 哈希函数需要的种子值
  uint32_t hash_seed; 
} HashMap;

// 创建一个固定容量的哈希表
HashMap* create_hashmap(void);
// 销毁一个哈希表
void destroy_hashmap(HashMap* map);

// 插入一个键值对
V put(HashMap* map, K key, V val);
// 查询一个键值对
V get(HashMap* map, K key);
// 删除某个键值对
bool map_remove(HashMap* map, K key);