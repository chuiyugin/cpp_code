#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <error.h>
#include <errno.h>

int g_value = 10; // 数据段

int main(int argc, char* argv[])
{
    // ./test_fork2
    int l_value = 20; // 栈
    int* d_value = (int*)malloc(sizeof(int)); // 堆
    *d_value = 30;

    //惯用法
    //父子进程都是从fork()返回
    //子进程不会执行前面的代码
    pid_t pid = fork(); 

    switch(pid){
        case -1:
            //出错
            error(1, errno, "fork");
        case 0:
            //子进程
            g_value += 100;
            l_value += 100;
            *d_value += 100;
            printf("g_value = %d, l_value = %d, d_value = %d\n", g_value, l_value, *d_value);
            exit(0);
        default:
            //父进程
            sleep(2);
            printf("g_value = %d, l_value = %d, d_value = %d\n", g_value, l_value, *d_value);
            exit(0);
    }
    return 0;
}