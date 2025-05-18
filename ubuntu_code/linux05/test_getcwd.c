#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char* cwd;
    if((cwd = getcwd(NULL,0)) == NULL)
    {
        //错误处理
        perror("getcwd");
        exit(1);
    }

    puts(cwd);
    free(cwd);//由用户来free

    return 0;
}

