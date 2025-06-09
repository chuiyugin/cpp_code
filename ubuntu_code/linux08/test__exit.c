#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>

//执行一些资源清理操作
void func(void){
    printf("Something going to die...");
}

int main(int argc, char* argv[])
{
    // ./test__exit
    // 调用atexit()注册函数
    int err = atexit(func);
    if(err != 0){
        error(1, 0, "atexit()");
    }

    //正常执行程序...
    printf("Hello world");

    _exit(123);

    return 0;
}