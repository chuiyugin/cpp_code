#include "hashmap.h"

int main(void)
{
    //创建空的哈希表
    HashMap* map = create_hashmap();

    //向哈希表写入数据
    put(map, "test", "123");
    put(map, "test1", "234");
    put(map, "test2", "345");

    V val_2 = get(map,"test1");
    puts(val_2);

    put(map, "test2", NULL);
    put(map, "test1", "456");

    V val_1 = get(map,"test1");
    puts(val_1);

    map_remove(map,"test1");

    V val_3 = get(map,"test1");
    puts(val_3);

    if(get(map,"test1")==NULL)
        printf("empty!\n");
    else
        puts(val_3);

    // 销毁哈希表
    destroy_hashmap(map);
    printf("sucess!\n");

    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}