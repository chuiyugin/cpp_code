#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    // ./test_environ
    // 打印进程的pid
    printf("pid = %d, ppid = %d\n", getpid(), getppid());

    // 打印命令行参数
    for(int i=0; i<argc; i++){
        puts(argv[i]);
    }
    printf("-----------------------------\n");
    // 打印环境变量
    // 声明外部变量(引用其它文件定义的environ变量)
    extern char** environ; 
    char** cur = environ;
    while(*cur){
        puts(*cur);
        cur++;
    }
    return 0;
}