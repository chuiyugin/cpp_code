#include "Vector.h" //""：搜索路径：当前目录 -> 系统的头文件包含的目录下
#include <stdio.h>  //<>：搜索路径：系统的头文件包含目录下
#include <stdlib.h>


int main(void)
{
    //创建空的动态数组
    Vector* v = vector_create();

    for(int i=0; i<200; i++)
    {
        push_back(v,i);
    }
    printf("push_finish\n");
    vector_destroy(v);
    printf("destroy_finish\n");
    system("pause"); // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}