#include "hashmap.h"

int main(void)
{
    //创建空的哈希表
    HashMap* map = create_hashmap();

    //向哈希表写入数据
    put(map, "test", "123");
    put(map, "test1", "234");
    put(map, "test2", "345");
    put(map, "test3", "567");
    put(map, "test4", "678");
    put(map, "test5", "789");
    put(map, "test6", "345");
    put(map, "test7", "567");
    put(map, "test8", "678");
    put(map, "test9", "789");

    V val_2 = get(map,"test9");
    puts(val_2);

    put(map, "test2", NULL);
    put(map, "test8", "456");

    V val_1 = get(map,"test8");
    puts(val_1);

    map_remove(map,"test6");

    V val_3 = get(map,"test7");
    puts(val_3);

    if(get(map,"test6")==NULL)
        printf("empty!\n");
    else
        puts(val_3);

    // 销毁哈希表
    destroy_hashmap(map);
    printf("sucess!\n");

    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}