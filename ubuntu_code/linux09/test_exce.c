#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>

// 定义新的环境变量
char* const new_env[] = {"USER=yugin", "TEST=0123", NULL};
// 使用execv函数簇的命令行参数向量
char* const args[] = {"./test_environ", "aaa", "bbb", "ccc", NULL};

int main(int argc, char* argv[])
{
    // ./test_exce
    // 打印进程的pid
    printf("pid = %d, ppid = %d\n", getpid(), getppid());

    printf("BEGIN:\n");

    //execl("test_environ", "./test_environ", "aaa", "bbb", "ccc", NULL);
    //p:会根据path环境变量查找可执行程序
    //execlp("test_environ", "./test_environ", "aaa", "bbb", "ccc", NULL);
    execle("test_environ", "./test_environ", "aaa", "bbb", "ccc", NULL, new_env);
    //execv("test_environ", args);
    //p:会根据path环境变量查找可执行程序
    //execvp("test_environ", args);
    //execve("test_environ", args, new_env);
    error(1, errno, "exce");

    return 0;
}