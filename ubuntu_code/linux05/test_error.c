#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <stdio.h>

int main()
{
    char cwd[20];
    if(getcwd(cwd,20) == NULL)
    {
        //错误处理
        error(1, errno, "getcwd");
    }

    puts(cwd);

    return 0;
}

